# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/zou/Documents/clion/clion-2023.2.1/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /home/zou/Documents/clion/clion-2023.2.1/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zou/Documents/DFIKOS

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zou/Documents/DFIKOS/cmake-build-debug

# Utility rule file for intrinsics_gen.

# Include any custom commands dependencies for this target.
include frontend/llvm/CMakeFiles/intrinsics_gen.dir/compiler_depend.make

# Include the progress variables for this target.
include frontend/llvm/CMakeFiles/intrinsics_gen.dir/progress.make

intrinsics_gen: frontend/llvm/CMakeFiles/intrinsics_gen.dir/build.make
.PHONY : intrinsics_gen

# Rule to build all files generated by this target.
frontend/llvm/CMakeFiles/intrinsics_gen.dir/build: intrinsics_gen
.PHONY : frontend/llvm/CMakeFiles/intrinsics_gen.dir/build

frontend/llvm/CMakeFiles/intrinsics_gen.dir/clean:
	cd /home/zou/Documents/DFIKOS/cmake-build-debug/frontend/llvm && $(CMAKE_COMMAND) -P CMakeFiles/intrinsics_gen.dir/cmake_clean.cmake
.PHONY : frontend/llvm/CMakeFiles/intrinsics_gen.dir/clean

frontend/llvm/CMakeFiles/intrinsics_gen.dir/depend:
	cd /home/zou/Documents/DFIKOS/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zou/Documents/DFIKOS /home/zou/Documents/DFIKOS/frontend/llvm /home/zou/Documents/DFIKOS/cmake-build-debug /home/zou/Documents/DFIKOS/cmake-build-debug/frontend/llvm /home/zou/Documents/DFIKOS/cmake-build-debug/frontend/llvm/CMakeFiles/intrinsics_gen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : frontend/llvm/CMakeFiles/intrinsics_gen.dir/depend

