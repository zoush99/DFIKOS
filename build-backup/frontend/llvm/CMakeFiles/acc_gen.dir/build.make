# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zou/Documents/DFIKOS

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zou/Documents/DFIKOS/build

# Utility rule file for acc_gen.

# Include the progress variables for this target.
include frontend/llvm/CMakeFiles/acc_gen.dir/progress.make

acc_gen: frontend/llvm/CMakeFiles/acc_gen.dir/build.make

.PHONY : acc_gen

# Rule to build all files generated by this target.
frontend/llvm/CMakeFiles/acc_gen.dir/build: acc_gen

.PHONY : frontend/llvm/CMakeFiles/acc_gen.dir/build

frontend/llvm/CMakeFiles/acc_gen.dir/clean:
	cd /home/zou/Documents/DFIKOS/build/frontend/llvm && $(CMAKE_COMMAND) -P CMakeFiles/acc_gen.dir/cmake_clean.cmake
.PHONY : frontend/llvm/CMakeFiles/acc_gen.dir/clean

frontend/llvm/CMakeFiles/acc_gen.dir/depend:
	cd /home/zou/Documents/DFIKOS/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zou/Documents/DFIKOS /home/zou/Documents/DFIKOS/frontend/llvm /home/zou/Documents/DFIKOS/build /home/zou/Documents/DFIKOS/build/frontend/llvm /home/zou/Documents/DFIKOS/build/frontend/llvm/CMakeFiles/acc_gen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : frontend/llvm/CMakeFiles/acc_gen.dir/depend

