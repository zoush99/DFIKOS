# CMake generated Testfile for 
# Source directory: /home/zou/Documents/DFIKOS/frontend/llvm/test/regression/import
# Build directory: /home/zou/Documents/DFIKOS/cmake-build-debug/frontend/llvm/test/regression/import
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(import-no-optimization "/usr/bin/bash" "runtest" "--ikos-import" "/home/zou/Documents/DFIKOS/cmake-build-debug/frontend/llvm/ikos-import" "--file-check" "/usr/lib/llvm-14/bin/FileCheck")
set_tests_properties(import-no-optimization PROPERTIES  WORKING_DIRECTORY "/home/zou/Documents/DFIKOS/frontend/llvm/test/regression/import/no_optimization" _BACKTRACE_TRIPLES "/home/zou/Documents/DFIKOS/frontend/llvm/test/regression/import/CMakeLists.txt;26;add_test;/home/zou/Documents/DFIKOS/frontend/llvm/test/regression/import/CMakeLists.txt;33;add_import_test;/home/zou/Documents/DFIKOS/frontend/llvm/test/regression/import/CMakeLists.txt;0;")
add_test(import-basic-optimization "/usr/bin/bash" "runtest" "--ikos-import" "/home/zou/Documents/DFIKOS/cmake-build-debug/frontend/llvm/ikos-import" "--file-check" "/usr/lib/llvm-14/bin/FileCheck")
set_tests_properties(import-basic-optimization PROPERTIES  WORKING_DIRECTORY "/home/zou/Documents/DFIKOS/frontend/llvm/test/regression/import/basic_optimization" _BACKTRACE_TRIPLES "/home/zou/Documents/DFIKOS/frontend/llvm/test/regression/import/CMakeLists.txt;26;add_test;/home/zou/Documents/DFIKOS/frontend/llvm/test/regression/import/CMakeLists.txt;34;add_import_test;/home/zou/Documents/DFIKOS/frontend/llvm/test/regression/import/CMakeLists.txt;0;")
add_test(import-aggressive-optimization "/usr/bin/bash" "runtest" "--ikos-import" "/home/zou/Documents/DFIKOS/cmake-build-debug/frontend/llvm/ikos-import" "--file-check" "/usr/lib/llvm-14/bin/FileCheck")
set_tests_properties(import-aggressive-optimization PROPERTIES  WORKING_DIRECTORY "/home/zou/Documents/DFIKOS/frontend/llvm/test/regression/import/aggressive_optimization" _BACKTRACE_TRIPLES "/home/zou/Documents/DFIKOS/frontend/llvm/test/regression/import/CMakeLists.txt;26;add_test;/home/zou/Documents/DFIKOS/frontend/llvm/test/regression/import/CMakeLists.txt;35;add_import_test;/home/zou/Documents/DFIKOS/frontend/llvm/test/regression/import/CMakeLists.txt;0;")
