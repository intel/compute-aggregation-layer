#
# Copyright (C) 2022 Intel Corporation
#
# SPDX-License-Identifier: MIT
#

import multiprocessing
import os
import sys
import yaml

from argparse import ArgumentParser

def create_argument_parser():
    arg_parser = ArgumentParser(prog = "run_blackbox_tests.py",
                                description = "This program is inteded to run blackbox tests according to the given configuration.")

    arg_parser.add_argument("--all-configs-path",
                            metavar='<YAML_CONFIGS_PATH>',
                            required=True,
                            help="A path to YAML file with available configurations.")

    arg_parser.add_argument("--selected-config",
                            metavar='<NAME>',
                            required=True,
                            help="A config entry from YAML file, which will be used.")

    arg_parser.add_argument("--binaries-dir",
                            metavar='<BIN_PATH>',
                            required=True,
                            help="A path to binaries of tests.")

    return arg_parser

def get_config_entry(configs_path, selected_config):
    with open(configs_path, "r", encoding="utf-8") as f:
        configs = yaml.load(f, Loader=yaml.Loader)

    if not selected_config in configs.keys():
        print(f"Error: unknown config! Available configs: {str(configs.keys())}")
        sys.exit(-1)

    return configs[selected_config]

def ensure_binaries_exist(bin_dir_root, config):
    for test_name, test_desc in config.items():
        if not "test_binary" in test_desc:
            print(f"Error: test description does not contain binary path! test_desc = {str(test_desc)}");
            sys.exit(-1)

        test_binary_path = os.path.join(bin_dir_root, test_desc["test_binary"])
        if not os.path.exists(test_binary_path):
            print(f"Error: path to test binary is invalid! test_binary_path = '{test_binary_path}'");
            sys.exit(-1)

def run_all_tests(bin_dir_root, config):
    processes = {}

    for test_name, test_desc in config.items():
        processes[test_name] = multiprocessing.Process(target=single_test_body, args=(test_name, bin_dir_root, test_desc))
        processes[test_name].start()

        print(f"Started test: '{test_name}' in a separate process. PID = {processes[test_name].pid}")

    failed_tests = []
    for test_name, test_process in processes.items():
        test_process.join()
        print(f"Finished test: '{test_name}'. Exit code = {test_process.exitcode}")

        if test_process.exitcode != 0:
            failed_tests.append(test_name);

    if failed_tests:
        print(f"{len(failed_tests)} tests failed! Result: FAILURE!\n")

        failed_tests_str = "\n".join(failed_tests)
        print(f"Failed tests:\n{failed_tests_str}")
    else:
        print("All tests passed! Result: SUCCESS!")

def single_test_body(test_name, bin_dir_root, test_desc):
    preserve_logs = test_desc.get("preserve_logs", False)
    redirect_output_streams(test_name, bin_dir_root, preserve_logs)

    test_binary = test_desc["test_binary"]
    test_args = test_desc.get("test_args", "")
    test_binary_path = os.path.join(bin_dir_root, test_binary)

    result = os.system(f"calrun {test_binary_path} {test_args}")
    sys.exit(-1 if result != 0 else 0)

def redirect_output_streams(test_name, bin_dir_root, preserve_logs):
    output_logs_path = os.devnull if not preserve_logs else os.path.join(bin_dir_root, f"blackbox_{test_name}.txt")
    output_logs_file = open(output_logs_path, 'w')

    os.dup2(output_logs_file.fileno(), sys.stdout.fileno())
    os.dup2(output_logs_file.fileno(), sys.stderr.fileno())

def main():
    arg_parser = create_argument_parser()
    args = arg_parser.parse_args()

    config = get_config_entry(args.all_configs_path, args.selected_config)
    ensure_binaries_exist(args.binaries_dir, config)

    run_all_tests(args.binaries_dir, config)

if __name__ == "__main__":
    multiprocessing.set_start_method('spawn')
    main()
