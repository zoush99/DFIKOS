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
CMAKE_BINARY_DIR = /home/zou/Documents/DFIKOS/Build

# Include any dependencies generated for this target.
include core/test/unit/CMakeFiles/test-core-domain-machine_int-congruence.dir/depend.make

# Include the progress variables for this target.
include core/test/unit/CMakeFiles/test-core-domain-machine_int-congruence.dir/progress.make

# Include the compile flags for this target's objects.
include core/test/unit/CMakeFiles/test-core-domain-machine_int-congruence.dir/flags.make

core/test/unit/CMakeFiles/test-core-domain-machine_int-congruence.dir/domain/machine_int/congruence.cpp.o: core/test/unit/CMakeFiles/test-core-domain-machine_int-congruence.dir/flags.make
core/test/unit/CMakeFiles/test-core-domain-machine_int-congruence.dir/domain/machine_int/congruence.cpp.o: ../core/test/unit/domain/machine_int/congruence.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zou/Documents/DFIKOS/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object core/test/unit/CMakeFiles/test-core-domain-machine_int-congruence.dir/domain/machine_int/congruence.cpp.o"
	cd /home/zou/Documents/DFIKOS/Build/core/test/unit && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test-core-domain-machine_int-congruence.dir/domain/machine_int/congruence.cpp.o -c /home/zou/Documents/DFIKOS/core/test/unit/domain/machine_int/congruence.cpp

core/test/unit/CMakeFiles/test-core-domain-machine_int-congruence.dir/domain/machine_int/congruence.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test-core-domain-machine_int-congruence.dir/domain/machine_int/congruence.cpp.i"
	cd /home/zou/Documents/DFIKOS/Build/core/test/unit && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zou/Documents/DFIKOS/core/test/unit/domain/machine_int/congruence.cpp > CMakeFiles/test-core-domain-machine_int-congruence.dir/domain/machine_int/congruence.cpp.i

core/test/unit/CMakeFiles/test-core-domain-machine_int-congruence.dir/domain/machine_int/congruence.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test-core-domain-machine_int-congruence.dir/domain/machine_int/congruence.cpp.s"
	cd /home/zou/Documents/DFIKOS/Build/core/test/unit && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zou/Documents/DFIKOS/core/test/unit/domain/machine_int/congruence.cpp -o CMakeFiles/test-core-domain-machine_int-congruence.dir/domain/machine_int/congruence.cpp.s

# Object files for target test-core-domain-machine_int-congruence
test__core__domain__machine_int__congruence_OBJECTS = \
"CMakeFiles/test-core-domain-machine_int-congruence.dir/domain/machine_int/congruence.cpp.o"

# External object files for target test-core-domain-machine_int-congruence
test__core__domain__machine_int__congruence_EXTERNAL_OBJECTS =

core/test/unit/test-core-domain-machine_int-congruence: core/test/unit/CMakeFiles/test-core-domain-machine_int-congruence.dir/domain/machine_int/congruence.cpp.o
core/test/unit/test-core-domain-machine_int-congruence: core/test/unit/CMakeFiles/test-core-domain-machine_int-congruence.dir/build.make
core/test/unit/test-core-domain-machine_int-congruence: /usr/lib/x86_64-linux-gnu/libgmpxx.so
core/test/unit/test-core-domain-machine_int-congruence: /usr/lib/x86_64-linux-gnu/libgmp.so
core/test/unit/test-core-domain-machine_int-congruence: /usr/lib/x86_64-linux-gnu/libboost_unit_test_framework.so.1.71.0
core/test/unit/test-core-domain-machine_int-congruence: /usr/local/apron/lib/libapron.so
core/test/unit/test-core-domain-machine_int-congruence: /usr/local/apron/lib/libboxMPQ.so
core/test/unit/test-core-domain-machine_int-congruence: /usr/local/apron/lib/liboctMPQ.so
core/test/unit/test-core-domain-machine_int-congruence: /usr/local/apron/lib/libpolkaMPQ.so
core/test/unit/test-core-domain-machine_int-congruence: /usr/local/apron/lib/libap_ppl.so
core/test/unit/test-core-domain-machine_int-congruence: /usr/local/apron/lib/libap_pkgrid.so
core/test/unit/test-core-domain-machine_int-congruence: /usr/lib/x86_64-linux-gnu/libgmp.so
core/test/unit/test-core-domain-machine_int-congruence: /usr/lib/x86_64-linux-gnu/libgmpxx.so
core/test/unit/test-core-domain-machine_int-congruence: /usr/local/lib/libmpfr.so
core/test/unit/test-core-domain-machine_int-congruence: /usr/lib/x86_64-linux-gnu/libppl.so
core/test/unit/test-core-domain-machine_int-congruence: /usr/local/apron/lib/libapron.so
core/test/unit/test-core-domain-machine_int-congruence: /usr/local/apron/lib/libboxMPQ.so
core/test/unit/test-core-domain-machine_int-congruence: /usr/local/apron/lib/liboctMPQ.so
core/test/unit/test-core-domain-machine_int-congruence: /usr/local/apron/lib/libpolkaMPQ.so
core/test/unit/test-core-domain-machine_int-congruence: /usr/local/apron/lib/libap_ppl.so
core/test/unit/test-core-domain-machine_int-congruence: /usr/local/apron/lib/libap_pkgrid.so
core/test/unit/test-core-domain-machine_int-congruence: /usr/local/lib/libmpfr.so
core/test/unit/test-core-domain-machine_int-congruence: /usr/lib/x86_64-linux-gnu/libppl.so
core/test/unit/test-core-domain-machine_int-congruence: core/test/unit/CMakeFiles/test-core-domain-machine_int-congruence.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zou/Documents/DFIKOS/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test-core-domain-machine_int-congruence"
	cd /home/zou/Documents/DFIKOS/Build/core/test/unit && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test-core-domain-machine_int-congruence.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
core/test/unit/CMakeFiles/test-core-domain-machine_int-congruence.dir/build: core/test/unit/test-core-domain-machine_int-congruence

.PHONY : core/test/unit/CMakeFiles/test-core-domain-machine_int-congruence.dir/build

core/test/unit/CMakeFiles/test-core-domain-machine_int-congruence.dir/clean:
	cd /home/zou/Documents/DFIKOS/Build/core/test/unit && $(CMAKE_COMMAND) -P CMakeFiles/test-core-domain-machine_int-congruence.dir/cmake_clean.cmake
.PHONY : core/test/unit/CMakeFiles/test-core-domain-machine_int-congruence.dir/clean

core/test/unit/CMakeFiles/test-core-domain-machine_int-congruence.dir/depend:
	cd /home/zou/Documents/DFIKOS/Build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zou/Documents/DFIKOS /home/zou/Documents/DFIKOS/core/test/unit /home/zou/Documents/DFIKOS/Build /home/zou/Documents/DFIKOS/Build/core/test/unit /home/zou/Documents/DFIKOS/Build/core/test/unit/CMakeFiles/test-core-domain-machine_int-congruence.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : core/test/unit/CMakeFiles/test-core-domain-machine_int-congruence.dir/depend

