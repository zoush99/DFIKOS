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

# Include any dependencies generated for this target.
include core/test/unit/CMakeFiles/test-core-adt-patricia_tree-map.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include core/test/unit/CMakeFiles/test-core-adt-patricia_tree-map.dir/compiler_depend.make

# Include the progress variables for this target.
include core/test/unit/CMakeFiles/test-core-adt-patricia_tree-map.dir/progress.make

# Include the compile flags for this target's objects.
include core/test/unit/CMakeFiles/test-core-adt-patricia_tree-map.dir/flags.make

core/test/unit/CMakeFiles/test-core-adt-patricia_tree-map.dir/adt/patricia_tree/map.cpp.o: core/test/unit/CMakeFiles/test-core-adt-patricia_tree-map.dir/flags.make
core/test/unit/CMakeFiles/test-core-adt-patricia_tree-map.dir/adt/patricia_tree/map.cpp.o: /home/zou/Documents/DFIKOS/core/test/unit/adt/patricia_tree/map.cpp
core/test/unit/CMakeFiles/test-core-adt-patricia_tree-map.dir/adt/patricia_tree/map.cpp.o: core/test/unit/CMakeFiles/test-core-adt-patricia_tree-map.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zou/Documents/DFIKOS/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object core/test/unit/CMakeFiles/test-core-adt-patricia_tree-map.dir/adt/patricia_tree/map.cpp.o"
	cd /home/zou/Documents/DFIKOS/cmake-build-debug/core/test/unit && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT core/test/unit/CMakeFiles/test-core-adt-patricia_tree-map.dir/adt/patricia_tree/map.cpp.o -MF CMakeFiles/test-core-adt-patricia_tree-map.dir/adt/patricia_tree/map.cpp.o.d -o CMakeFiles/test-core-adt-patricia_tree-map.dir/adt/patricia_tree/map.cpp.o -c /home/zou/Documents/DFIKOS/core/test/unit/adt/patricia_tree/map.cpp

core/test/unit/CMakeFiles/test-core-adt-patricia_tree-map.dir/adt/patricia_tree/map.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test-core-adt-patricia_tree-map.dir/adt/patricia_tree/map.cpp.i"
	cd /home/zou/Documents/DFIKOS/cmake-build-debug/core/test/unit && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zou/Documents/DFIKOS/core/test/unit/adt/patricia_tree/map.cpp > CMakeFiles/test-core-adt-patricia_tree-map.dir/adt/patricia_tree/map.cpp.i

core/test/unit/CMakeFiles/test-core-adt-patricia_tree-map.dir/adt/patricia_tree/map.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test-core-adt-patricia_tree-map.dir/adt/patricia_tree/map.cpp.s"
	cd /home/zou/Documents/DFIKOS/cmake-build-debug/core/test/unit && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zou/Documents/DFIKOS/core/test/unit/adt/patricia_tree/map.cpp -o CMakeFiles/test-core-adt-patricia_tree-map.dir/adt/patricia_tree/map.cpp.s

# Object files for target test-core-adt-patricia_tree-map
test__core__adt__patricia_tree__map_OBJECTS = \
"CMakeFiles/test-core-adt-patricia_tree-map.dir/adt/patricia_tree/map.cpp.o"

# External object files for target test-core-adt-patricia_tree-map
test__core__adt__patricia_tree__map_EXTERNAL_OBJECTS =

core/test/unit/test-core-adt-patricia_tree-map: core/test/unit/CMakeFiles/test-core-adt-patricia_tree-map.dir/adt/patricia_tree/map.cpp.o
core/test/unit/test-core-adt-patricia_tree-map: core/test/unit/CMakeFiles/test-core-adt-patricia_tree-map.dir/build.make
core/test/unit/test-core-adt-patricia_tree-map: /usr/lib/x86_64-linux-gnu/libgmpxx.so
core/test/unit/test-core-adt-patricia_tree-map: /usr/lib/x86_64-linux-gnu/libgmp.so
core/test/unit/test-core-adt-patricia_tree-map: /usr/lib/x86_64-linux-gnu/libboost_unit_test_framework.so.1.71.0
core/test/unit/test-core-adt-patricia_tree-map: /usr/local/lib/libmpfr.so
core/test/unit/test-core-adt-patricia_tree-map: /usr/local/apron/lib/libapron.so
core/test/unit/test-core-adt-patricia_tree-map: /usr/local/apron/lib/libboxMPQ.so
core/test/unit/test-core-adt-patricia_tree-map: /usr/local/apron/lib/liboctMPQ.so
core/test/unit/test-core-adt-patricia_tree-map: /usr/local/apron/lib/libpolkaMPQ.so
core/test/unit/test-core-adt-patricia_tree-map: /usr/local/apron/lib/libap_ppl.so
core/test/unit/test-core-adt-patricia_tree-map: /usr/local/apron/lib/libap_pkgrid.so
core/test/unit/test-core-adt-patricia_tree-map: /usr/lib/x86_64-linux-gnu/libgmp.so
core/test/unit/test-core-adt-patricia_tree-map: /usr/lib/x86_64-linux-gnu/libgmpxx.so
core/test/unit/test-core-adt-patricia_tree-map: /usr/local/lib/libmpfr.so
core/test/unit/test-core-adt-patricia_tree-map: /usr/lib/x86_64-linux-gnu/libppl.so
core/test/unit/test-core-adt-patricia_tree-map: /usr/local/apron/lib/libapron.so
core/test/unit/test-core-adt-patricia_tree-map: /usr/local/apron/lib/libboxMPQ.so
core/test/unit/test-core-adt-patricia_tree-map: /usr/local/apron/lib/liboctMPQ.so
core/test/unit/test-core-adt-patricia_tree-map: /usr/local/apron/lib/libpolkaMPQ.so
core/test/unit/test-core-adt-patricia_tree-map: /usr/local/apron/lib/libap_ppl.so
core/test/unit/test-core-adt-patricia_tree-map: /usr/local/apron/lib/libap_pkgrid.so
core/test/unit/test-core-adt-patricia_tree-map: /usr/lib/x86_64-linux-gnu/libppl.so
core/test/unit/test-core-adt-patricia_tree-map: core/test/unit/CMakeFiles/test-core-adt-patricia_tree-map.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zou/Documents/DFIKOS/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test-core-adt-patricia_tree-map"
	cd /home/zou/Documents/DFIKOS/cmake-build-debug/core/test/unit && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test-core-adt-patricia_tree-map.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
core/test/unit/CMakeFiles/test-core-adt-patricia_tree-map.dir/build: core/test/unit/test-core-adt-patricia_tree-map
.PHONY : core/test/unit/CMakeFiles/test-core-adt-patricia_tree-map.dir/build

core/test/unit/CMakeFiles/test-core-adt-patricia_tree-map.dir/clean:
	cd /home/zou/Documents/DFIKOS/cmake-build-debug/core/test/unit && $(CMAKE_COMMAND) -P CMakeFiles/test-core-adt-patricia_tree-map.dir/cmake_clean.cmake
.PHONY : core/test/unit/CMakeFiles/test-core-adt-patricia_tree-map.dir/clean

core/test/unit/CMakeFiles/test-core-adt-patricia_tree-map.dir/depend:
	cd /home/zou/Documents/DFIKOS/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zou/Documents/DFIKOS /home/zou/Documents/DFIKOS/core/test/unit /home/zou/Documents/DFIKOS/cmake-build-debug /home/zou/Documents/DFIKOS/cmake-build-debug/core/test/unit /home/zou/Documents/DFIKOS/cmake-build-debug/core/test/unit/CMakeFiles/test-core-adt-patricia_tree-map.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : core/test/unit/CMakeFiles/test-core-adt-patricia_tree-map.dir/depend

