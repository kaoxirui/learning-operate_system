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
CMAKE_SOURCE_DIR = /home/kao/learning-operate_system

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kao/learning-operate_system/build

# Include any dependencies generated for this target.
include CMakeFiles/DeadLock.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/DeadLock.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DeadLock.dir/flags.make

CMakeFiles/DeadLock.dir/src/DeadLock.cpp.o: CMakeFiles/DeadLock.dir/flags.make
CMakeFiles/DeadLock.dir/src/DeadLock.cpp.o: ../src/DeadLock.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kao/learning-operate_system/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/DeadLock.dir/src/DeadLock.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DeadLock.dir/src/DeadLock.cpp.o -c /home/kao/learning-operate_system/src/DeadLock.cpp

CMakeFiles/DeadLock.dir/src/DeadLock.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DeadLock.dir/src/DeadLock.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kao/learning-operate_system/src/DeadLock.cpp > CMakeFiles/DeadLock.dir/src/DeadLock.cpp.i

CMakeFiles/DeadLock.dir/src/DeadLock.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DeadLock.dir/src/DeadLock.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kao/learning-operate_system/src/DeadLock.cpp -o CMakeFiles/DeadLock.dir/src/DeadLock.cpp.s

# Object files for target DeadLock
DeadLock_OBJECTS = \
"CMakeFiles/DeadLock.dir/src/DeadLock.cpp.o"

# External object files for target DeadLock
DeadLock_EXTERNAL_OBJECTS =

DeadLock: CMakeFiles/DeadLock.dir/src/DeadLock.cpp.o
DeadLock: CMakeFiles/DeadLock.dir/build.make
DeadLock: CMakeFiles/DeadLock.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kao/learning-operate_system/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable DeadLock"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DeadLock.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DeadLock.dir/build: DeadLock

.PHONY : CMakeFiles/DeadLock.dir/build

CMakeFiles/DeadLock.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DeadLock.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DeadLock.dir/clean

CMakeFiles/DeadLock.dir/depend:
	cd /home/kao/learning-operate_system/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kao/learning-operate_system /home/kao/learning-operate_system /home/kao/learning-operate_system/build /home/kao/learning-operate_system/build /home/kao/learning-operate_system/build/CMakeFiles/DeadLock.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DeadLock.dir/depend

