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
include frontend/llvm/CMakeFiles/ikos-import.dir/depend.make

# Include the progress variables for this target.
include frontend/llvm/CMakeFiles/ikos-import.dir/progress.make

# Include the compile flags for this target's objects.
include frontend/llvm/CMakeFiles/ikos-import.dir/flags.make

frontend/llvm/CMakeFiles/ikos-import.dir/src/ikos_import.cpp.o: frontend/llvm/CMakeFiles/ikos-import.dir/flags.make
frontend/llvm/CMakeFiles/ikos-import.dir/src/ikos_import.cpp.o: ../frontend/llvm/src/ikos_import.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zou/Documents/DFIKOS/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object frontend/llvm/CMakeFiles/ikos-import.dir/src/ikos_import.cpp.o"
	cd /home/zou/Documents/DFIKOS/Build/frontend/llvm && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ikos-import.dir/src/ikos_import.cpp.o -c /home/zou/Documents/DFIKOS/frontend/llvm/src/ikos_import.cpp

frontend/llvm/CMakeFiles/ikos-import.dir/src/ikos_import.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ikos-import.dir/src/ikos_import.cpp.i"
	cd /home/zou/Documents/DFIKOS/Build/frontend/llvm && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zou/Documents/DFIKOS/frontend/llvm/src/ikos_import.cpp > CMakeFiles/ikos-import.dir/src/ikos_import.cpp.i

frontend/llvm/CMakeFiles/ikos-import.dir/src/ikos_import.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ikos-import.dir/src/ikos_import.cpp.s"
	cd /home/zou/Documents/DFIKOS/Build/frontend/llvm && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zou/Documents/DFIKOS/frontend/llvm/src/ikos_import.cpp -o CMakeFiles/ikos-import.dir/src/ikos_import.cpp.s

# Object files for target ikos-import
ikos__import_OBJECTS = \
"CMakeFiles/ikos-import.dir/src/ikos_import.cpp.o"

# External object files for target ikos-import
ikos__import_EXTERNAL_OBJECTS =

frontend/llvm/ikos-import: frontend/llvm/CMakeFiles/ikos-import.dir/src/ikos_import.cpp.o
frontend/llvm/ikos-import: frontend/llvm/CMakeFiles/ikos-import.dir/build.make
frontend/llvm/ikos-import: frontend/llvm/libikos-llvm-to-ar.a
frontend/llvm/ikos-import: /usr/lib/llvm-14/lib/libLLVMCore.a
frontend/llvm/ikos-import: /usr/lib/llvm-14/lib/libLLVMipo.a
frontend/llvm/ikos-import: /usr/lib/llvm-14/lib/libLLVMIRReader.a
frontend/llvm/ikos-import: /usr/lib/llvm-14/lib/libLLVMSupport.a
frontend/llvm/ikos-import: /usr/lib/llvm-14/lib/libLLVMTransformUtils.a
frontend/llvm/ikos-import: ar/libikos-ar.a
frontend/llvm/ikos-import: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so.1.71.0
frontend/llvm/ikos-import: /usr/lib/x86_64-linux-gnu/libboost_system.so.1.71.0
frontend/llvm/ikos-import: /usr/lib/x86_64-linux-gnu/libgmp.so
frontend/llvm/ikos-import: /usr/lib/x86_64-linux-gnu/libgmpxx.so
frontend/llvm/ikos-import: /usr/lib/llvm-14/lib/libLLVMAsmParser.a
frontend/llvm/ikos-import: /usr/lib/llvm-14/lib/libLLVMBitWriter.a
frontend/llvm/ikos-import: /usr/lib/llvm-14/lib/libLLVMFrontendOpenMP.a
frontend/llvm/ikos-import: /usr/lib/llvm-14/lib/libLLVMLinker.a
frontend/llvm/ikos-import: /usr/lib/llvm-14/lib/libLLVMScalarOpts.a
frontend/llvm/ikos-import: /usr/lib/llvm-14/lib/libLLVMAggressiveInstCombine.a
frontend/llvm/ikos-import: /usr/lib/llvm-14/lib/libLLVMInstCombine.a
frontend/llvm/ikos-import: /usr/lib/llvm-14/lib/libLLVMVectorize.a
frontend/llvm/ikos-import: /usr/lib/llvm-14/lib/libLLVMInstrumentation.a
frontend/llvm/ikos-import: /usr/lib/llvm-14/lib/libLLVMTransformUtils.a
frontend/llvm/ikos-import: /usr/lib/llvm-14/lib/libLLVMAnalysis.a
frontend/llvm/ikos-import: /usr/lib/llvm-14/lib/libLLVMProfileData.a
frontend/llvm/ikos-import: /usr/lib/llvm-14/lib/libLLVMDebugInfoDWARF.a
frontend/llvm/ikos-import: /usr/lib/llvm-14/lib/libLLVMObject.a
frontend/llvm/ikos-import: /usr/lib/llvm-14/lib/libLLVMBitReader.a
frontend/llvm/ikos-import: /usr/lib/llvm-14/lib/libLLVMCore.a
frontend/llvm/ikos-import: /usr/lib/llvm-14/lib/libLLVMRemarks.a
frontend/llvm/ikos-import: /usr/lib/llvm-14/lib/libLLVMBitstreamReader.a
frontend/llvm/ikos-import: /usr/lib/llvm-14/lib/libLLVMMCParser.a
frontend/llvm/ikos-import: /usr/lib/llvm-14/lib/libLLVMTextAPI.a
frontend/llvm/ikos-import: /usr/lib/llvm-14/lib/libLLVMMC.a
frontend/llvm/ikos-import: /usr/lib/llvm-14/lib/libLLVMBinaryFormat.a
frontend/llvm/ikos-import: /usr/lib/llvm-14/lib/libLLVMDebugInfoCodeView.a
frontend/llvm/ikos-import: /usr/lib/llvm-14/lib/libLLVMSupport.a
frontend/llvm/ikos-import: /usr/lib/x86_64-linux-gnu/libz.so
frontend/llvm/ikos-import: /usr/lib/x86_64-linux-gnu/libtinfo.so
frontend/llvm/ikos-import: /usr/lib/llvm-14/lib/libLLVMDemangle.a
frontend/llvm/ikos-import: frontend/llvm/CMakeFiles/ikos-import.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zou/Documents/DFIKOS/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ikos-import"
	cd /home/zou/Documents/DFIKOS/Build/frontend/llvm && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ikos-import.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
frontend/llvm/CMakeFiles/ikos-import.dir/build: frontend/llvm/ikos-import

.PHONY : frontend/llvm/CMakeFiles/ikos-import.dir/build

frontend/llvm/CMakeFiles/ikos-import.dir/clean:
	cd /home/zou/Documents/DFIKOS/Build/frontend/llvm && $(CMAKE_COMMAND) -P CMakeFiles/ikos-import.dir/cmake_clean.cmake
.PHONY : frontend/llvm/CMakeFiles/ikos-import.dir/clean

frontend/llvm/CMakeFiles/ikos-import.dir/depend:
	cd /home/zou/Documents/DFIKOS/Build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zou/Documents/DFIKOS /home/zou/Documents/DFIKOS/frontend/llvm /home/zou/Documents/DFIKOS/Build /home/zou/Documents/DFIKOS/Build/frontend/llvm /home/zou/Documents/DFIKOS/Build/frontend/llvm/CMakeFiles/ikos-import.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : frontend/llvm/CMakeFiles/ikos-import.dir/depend

