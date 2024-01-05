#
# Copyright (C) 2022-2024 Intel Corporation
#
# SPDX-License-Identifier: MIT
#

import os
import itertools
import sys

def assert_empty(list, error_message):
    if list:
        print(error_message)
        exit(-1)
        
def read_file(path):
    with open(path, "r") as f:
        return f.read()

def compare_dir(ref_base, test_base, subdir):
    reference_path = os.path.join(ref_base, subdir)
    tested_path = os.path.join(test_base, subdir)
    print(f"Reference : {reference_path}")
    print(f"Tested : {tested_path}")

    reference_file_names = os.listdir(reference_path)
    tested_file_names = os.listdir(tested_path)
    
    not_in_reference = [file_name for file_name in tested_file_names if file_name not in reference_file_names]
    not_in_tested = [file_name for file_name in reference_file_names if file_name not in tested_file_names]
    
    assert_empty(not_in_reference, f"ERROR : Excessive files in {tested_path} : {not_in_reference}")
    assert_empty(not_in_tested, f"ERROR : Missing files in {tested_path} : {not_in_tested}")
    common_file_names = reference_file_names
    
    for fname in common_file_names:
        ref_path = os.path.join(reference_path, fname)
        test_path = os.path.join(tested_path, fname)
        if os.path.isdir(ref_path) != os.path.isdir(test_path):
            print(f"ERROR : File {'is' if os.path.isdir(ref_path) else 'is not'} supposed to be a directory for {test_path}")
            exit(-1)
        if os.path.isdir(ref_path):
            continue
        reference = read_file(ref_path)
        tested = read_file(test_path)      
        if not os.path.isdir(reference) and (tested != reference):
            print(f"ERROR : File contents mismatch for {os.path.join(subdir, fname)}")
            exit(-1)

    for fname in common_file_names:
        ref_path = os.path.join(reference_path, fname)
        if os.path.isdir(ref_path):
            compare_dir(ref_base, test_base, os.path.join(subdir, fname))
            
    print(f"PASSED : Everything looks GOOD for {common_file_names}")

def main():
    if len(sys.argv) < 3:
        print("Expected exactly 2 arguments : reference_path and tested_path")
        exit(-1)
        
    reference_path = sys.argv[1]
    tested_path = sys.argv[2]
    compare_dir(reference_path, tested_path, "")


if __name__ == "__main__":
    main()
