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
include core/test/unit/CMakeFiles/test-core-domain-numeric-gauge.dir/depend.make

# Include the progress variables for this target.
include core/test/unit/CMakeFiles/test-core-domain-numeric-gauge.dir/progress.make

# Include the compile flags for this target's objects.
include core/test/unit/CMakeFiles/test-core-domain-numeric-gauge.dir/flags.make

core/test/unit/CMakeFiles/test-core-domain-numeric-gauge.dir/domain/numeric/gauge.cpp.o: core/test/unit/CMakeFiles/test-core-domain-numeric-gauge.dir/flags.make
core/test/unit/CMakeFiles/test-core-domain-numeric-gauge.dir/domain/numeric/gauge.cpp.o: ../core/test/unit/domain/numeric/gauge.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zou/Documents/DFIKOS/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object core/test/unit/CMakeFiles/test-core-domain-numeric-gauge.dir/domain/numeric/gauge.cpp.o"
	cd /home/zou/Documents/DFIKOS/Build/core/test/unit && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test-core-domain-numeric-gauge.dir/domain/numeric/gauge.cpp.o -c /home/zou/Documents/DFIKOS/core/test/unit/domain/numeric/gauge.cpp

core/test/unit/CMakeFiles/test-core-domain-numeric-gauge.dir/domain/numeric/gauge.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test-core-domain-numeric-gauge.dir/domain/numeric/gauge.cpp.i"
	cd /home/zou/Documents/DFIKOS/Build/core/test/unit && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zou/Documents/DFIKOS/core/test/unit/domain/numeric/gauge.cpp > CMakeFiles/test-core-domain-numeric-gauge.dir/domain/numeric/gauge.cpp.i

core/test/unit/CMakeFiles/test-core-domain-numeric-gauge.dir/domain/numeric/gauge.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test-core-domain-numeric-gauge.dir/domain/numeric/gauge.cpp.s"
	cd /home/zou/Documents/DFIKOS/Build/core/test/unit && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zou/Documents/DFIKOS/core/test/unit/domain/numeric/gauge.cpp -o CMakeFiles/test-core-domain-numeric-gauge.dir/domain/numeric/gauge.cpp.s

# Object files for target test-core-domain-numeric-gauge
test__core__domain__numeric__gauge_OBJECTS = \
"CMakeFiles/test-core-domain-numeric-gauge.dir/domain/numeric/gauge.cpp.o"

# External object files for target test-core-domain-numeric-gauge
test__core__domain__numeric__gauge_EXTERNAL_OBJECTS =

core/test/unit/test-core-domain-numeric-gauge: core/test/unit/CMakeFiles/test-core-domain-numeric-gauge.dir/domain/numeric/gauge.cpp.o
core/test/unit/test-core-domain-numeric-gauge: core/test/unit/CMakeFiles/test-core-domain-numeric-gauge.dir/build.make
core/test/unit/test-core-domain-numeric-gauge: /usr/lib/x86_64-linux-gnu/libgmpxx.so
core/test/unit/test-core-domain-numeric-gauge: /usr/lib/x86_64-linux-gnu/libgmp.so
core/test/unit/test-core-domain-numeric-gauge: /usr/lib/x86_64-linux-gnu/libboost_unit_test_framework.so.1.71.0
core/test/unit/test-core-domain-numeric-gauge: /usr/local/apron/lib/libapron.so
core/test/unit/test-core-domain-numeric-gauge: /usr/local/apron/lib/libboxMPQ.so
core/test/unit/test-core-domain-numeric-gauge: /usr/local/apron/lib/liboctMPQ.so
core/test/unit/test-core-domain-numeric-gauge: /usr/local/apron/lib/libpolkaMPQ.so
core/test/unit/test-core-domain-numeric-gauge: /usr/local/apron/lib/libap_ppl.so
core/test/unit/test-core-domain-numeric-gauge: /usr/local/apron/lib/libap_pkgrid.so
core/test/unit/test-core-domain-numeric-gauge: /usr/lib/x86_64-linux-gnu/libgmp.so
core/test/unit/test-core-domain-numeric-gauge: /usr/lib/x86_64-linux-gnu/libgmpxx.so
core/test/unit/test-core-domain-numeric-gauge: /usr/local/lib/libmpfr.so
core/test/unit/test-core-domain-numeric-gauge: /usr/lib/x86_64-linux-gnu/libppl.so
core/test/unit/test-core-domain-numeric-gauge: /usr/local/apron/lib/libapron.so
core/test/unit/test-core-domain-numeric-gauge: /usr/local/apron/lib/libboxMPQ.so
core/test/unit/test-core-domain-numeric-gauge: /usr/local/apron/lib/liboctMPQ.so
core/test/unit/test-core-domain-numeric-gauge: /usr/local/apron/lib/libpolkaMPQ.so
core/test/unit/test-core-domain-numeric-gauge: /usr/local/apron/lib/libap_ppl.so
core/test/unit/test-core-domain-numeric-gauge: /usr/local/apron/lib/libap_pkgrid.so
core/test/unit/test-core-domain-numeric-gauge: /usr/local/lib/libmpfr.so
core/test/unit/test-core-domain-numeric-gauge: /usr/lib/x86_64-linux-gnu/libppl.so
core/test/unit/test-core-domain-numeric-gauge: core/test/unit/CMakeFiles/test-core-domain-numeric-gauge.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zou/Documents/DFIKOS/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test-core-domain-numeric-gauge"
	cd /home/zou/Documents/DFIKOS/Build/core/test/unit && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test-core-domain-numeric-gauge.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
core/test/unit/CMakeFiles/test-core-domain-numeric-gauge.dir/build: core/test/unit/test-core-domain-numeric-gauge

.PHONY : core/test/unit/CMakeFiles/test-core-domain-numeric-gauge.dir/build

core/test/unit/CMakeFiles/test-core-domain-numeric-gauge.dir/clean:
	cd /home/zou/Documents/DFIKOS/Build/core/test/unit && $(CMAKE_COMMAND) -P CMakeFiles/test-core-domain-numeric-gauge.dir/cmake_clean.cmake
.PHONY : core/test/unit/CMakeFiles/test-core-domain-numeric-gauge.dir/clean

core/test/unit/CMakeFiles/test-core-domain-numeric-gauge.dir/depend:
	cd /home/zou/Documents/DFIKOS/Build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zou/Documents/DFIKOS /home/zou/Documents/DFIKOS/core/test/unit /home/zou/Documents/DFIKOS/Build /home/zou/Documents/DFIKOS/Build/core/test/unit /home/zou/Documents/DFIKOS/Build/core/test/unit/CMakeFiles/test-core-domain-numeric-gauge.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : core/test/unit/CMakeFiles/test-core-domain-numeric-gauge.dir/depend

