#
# Copyright (C) 2022 Intel Corporation
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

def main():
    if len(sys.argv) < 3:
        print("Expected exactly 2 arguments : reference_path and tested_path")
        exit(-1)
        
    reference_path = sys.argv[1]
    tested_path = sys.argv[2]
    
    print(f"Reference : {reference_path}")
    print(f"Tested : {tested_path}")

    reference_file_names = os.listdir(reference_path)
    tested_file_names = os.listdir(tested_path)
    
    not_in_reference = [file_name for file_name in tested_file_names if file_name not in reference_file_names]
    not_in_tested = [file_name for file_name in reference_file_names if file_name not in tested_file_names]
    
    assert_empty(not_in_reference, f"ERROR : Excessive files in {tested_path} : {not_in_reference}")
    assert_empty(not_in_tested, f"ERROR : Missing files in {tested_path} : {not_in_tested}")
    common_file_names = reference_file_names
    
    dirs = [os.path.join(dir, file) for dir, file in itertools.product([reference_path, tested_path], common_file_names) if os.path.isdir(os.path.join(dir, file))]
    assert_empty(dirs, f"ERROR : Unexpected directories : {dirs}")
    
    for fname in common_file_names:
        reference = read_file(os.path.join(reference_path, fname))
        tested = read_file(os.path.join(tested_path, fname))
        if tested != reference:
            print(f"ERROR : File contents mismatch for {fname}")
            exit(-1)
            
    print(f"PASSED : Everything looks GOOD for {common_file_names}")

if __name__ == "__main__":
    main()
