# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.14

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "F:\clion\CLion 2019.1.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "F:\clion\CLion 2019.1.4\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = F:\project\project6.2_3vnTest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = F:\project\project6.2_3vnTest\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/project6_2_3vnTest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/project6_2_3vnTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/project6_2_3vnTest.dir/flags.make

CMakeFiles/project6_2_3vnTest.dir/main.cpp.obj: CMakeFiles/project6_2_3vnTest.dir/flags.make
CMakeFiles/project6_2_3vnTest.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=F:\project\project6.2_3vnTest\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/project6_2_3vnTest.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\project6_2_3vnTest.dir\main.cpp.obj -c F:\project\project6.2_3vnTest\main.cpp

CMakeFiles/project6_2_3vnTest.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project6_2_3vnTest.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E F:\project\project6.2_3vnTest\main.cpp > CMakeFiles\project6_2_3vnTest.dir\main.cpp.i

CMakeFiles/project6_2_3vnTest.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project6_2_3vnTest.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S F:\project\project6.2_3vnTest\main.cpp -o CMakeFiles\project6_2_3vnTest.dir\main.cpp.s

CMakeFiles/project6_2_3vnTest.dir/SDL.cpp.obj: CMakeFiles/project6_2_3vnTest.dir/flags.make
CMakeFiles/project6_2_3vnTest.dir/SDL.cpp.obj: ../SDL.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=F:\project\project6.2_3vnTest\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/project6_2_3vnTest.dir/SDL.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\project6_2_3vnTest.dir\SDL.cpp.obj -c F:\project\project6.2_3vnTest\SDL.cpp

CMakeFiles/project6_2_3vnTest.dir/SDL.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project6_2_3vnTest.dir/SDL.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E F:\project\project6.2_3vnTest\SDL.cpp > CMakeFiles\project6_2_3vnTest.dir\SDL.cpp.i

CMakeFiles/project6_2_3vnTest.dir/SDL.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project6_2_3vnTest.dir/SDL.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S F:\project\project6.2_3vnTest\SDL.cpp -o CMakeFiles\project6_2_3vnTest.dir\SDL.cpp.s

# Object files for target project6_2_3vnTest
project6_2_3vnTest_OBJECTS = \
"CMakeFiles/project6_2_3vnTest.dir/main.cpp.obj" \
"CMakeFiles/project6_2_3vnTest.dir/SDL.cpp.obj"

# External object files for target project6_2_3vnTest
project6_2_3vnTest_EXTERNAL_OBJECTS =

project6_2_3vnTest.exe: CMakeFiles/project6_2_3vnTest.dir/main.cpp.obj
project6_2_3vnTest.exe: CMakeFiles/project6_2_3vnTest.dir/SDL.cpp.obj
project6_2_3vnTest.exe: CMakeFiles/project6_2_3vnTest.dir/build.make
project6_2_3vnTest.exe: CMakeFiles/project6_2_3vnTest.dir/linklibs.rsp
project6_2_3vnTest.exe: CMakeFiles/project6_2_3vnTest.dir/objects1.rsp
project6_2_3vnTest.exe: CMakeFiles/project6_2_3vnTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=F:\project\project6.2_3vnTest\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable project6_2_3vnTest.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\project6_2_3vnTest.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/project6_2_3vnTest.dir/build: project6_2_3vnTest.exe

.PHONY : CMakeFiles/project6_2_3vnTest.dir/build

CMakeFiles/project6_2_3vnTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\project6_2_3vnTest.dir\cmake_clean.cmake
.PHONY : CMakeFiles/project6_2_3vnTest.dir/clean

CMakeFiles/project6_2_3vnTest.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" F:\project\project6.2_3vnTest F:\project\project6.2_3vnTest F:\project\project6.2_3vnTest\cmake-build-debug F:\project\project6.2_3vnTest\cmake-build-debug F:\project\project6.2_3vnTest\cmake-build-debug\CMakeFiles\project6_2_3vnTest.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/project6_2_3vnTest.dir/depend
