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
CMAKE_SOURCE_DIR = "F:\project\web learnopengl\shaderMore"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "F:\project\web learnopengl\shaderMore\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/shaderMore.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/shaderMore.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/shaderMore.dir/flags.make

CMakeFiles/shaderMore.dir/main.cpp.obj: CMakeFiles/shaderMore.dir/flags.make
CMakeFiles/shaderMore.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="F:\project\web learnopengl\shaderMore\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/shaderMore.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\shaderMore.dir\main.cpp.obj -c "F:\project\web learnopengl\shaderMore\main.cpp"

CMakeFiles/shaderMore.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shaderMore.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "F:\project\web learnopengl\shaderMore\main.cpp" > CMakeFiles\shaderMore.dir\main.cpp.i

CMakeFiles/shaderMore.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shaderMore.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "F:\project\web learnopengl\shaderMore\main.cpp" -o CMakeFiles\shaderMore.dir\main.cpp.s

CMakeFiles/shaderMore.dir/glad.c.obj: CMakeFiles/shaderMore.dir/flags.make
CMakeFiles/shaderMore.dir/glad.c.obj: ../glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="F:\project\web learnopengl\shaderMore\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/shaderMore.dir/glad.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\shaderMore.dir\glad.c.obj   -c "F:\project\web learnopengl\shaderMore\glad.c"

CMakeFiles/shaderMore.dir/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shaderMore.dir/glad.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "F:\project\web learnopengl\shaderMore\glad.c" > CMakeFiles\shaderMore.dir\glad.c.i

CMakeFiles/shaderMore.dir/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shaderMore.dir/glad.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "F:\project\web learnopengl\shaderMore\glad.c" -o CMakeFiles\shaderMore.dir\glad.c.s

CMakeFiles/shaderMore.dir/Shader.cpp.obj: CMakeFiles/shaderMore.dir/flags.make
CMakeFiles/shaderMore.dir/Shader.cpp.obj: ../Shader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="F:\project\web learnopengl\shaderMore\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/shaderMore.dir/Shader.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\shaderMore.dir\Shader.cpp.obj -c "F:\project\web learnopengl\shaderMore\Shader.cpp"

CMakeFiles/shaderMore.dir/Shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shaderMore.dir/Shader.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "F:\project\web learnopengl\shaderMore\Shader.cpp" > CMakeFiles\shaderMore.dir\Shader.cpp.i

CMakeFiles/shaderMore.dir/Shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shaderMore.dir/Shader.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "F:\project\web learnopengl\shaderMore\Shader.cpp" -o CMakeFiles\shaderMore.dir\Shader.cpp.s

CMakeFiles/shaderMore.dir/init.cpp.obj: CMakeFiles/shaderMore.dir/flags.make
CMakeFiles/shaderMore.dir/init.cpp.obj: ../init.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="F:\project\web learnopengl\shaderMore\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/shaderMore.dir/init.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\shaderMore.dir\init.cpp.obj -c "F:\project\web learnopengl\shaderMore\init.cpp"

CMakeFiles/shaderMore.dir/init.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shaderMore.dir/init.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "F:\project\web learnopengl\shaderMore\init.cpp" > CMakeFiles\shaderMore.dir\init.cpp.i

CMakeFiles/shaderMore.dir/init.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shaderMore.dir/init.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "F:\project\web learnopengl\shaderMore\init.cpp" -o CMakeFiles\shaderMore.dir\init.cpp.s

# Object files for target shaderMore
shaderMore_OBJECTS = \
"CMakeFiles/shaderMore.dir/main.cpp.obj" \
"CMakeFiles/shaderMore.dir/glad.c.obj" \
"CMakeFiles/shaderMore.dir/Shader.cpp.obj" \
"CMakeFiles/shaderMore.dir/init.cpp.obj"

# External object files for target shaderMore
shaderMore_EXTERNAL_OBJECTS =

shaderMore.exe: CMakeFiles/shaderMore.dir/main.cpp.obj
shaderMore.exe: CMakeFiles/shaderMore.dir/glad.c.obj
shaderMore.exe: CMakeFiles/shaderMore.dir/Shader.cpp.obj
shaderMore.exe: CMakeFiles/shaderMore.dir/init.cpp.obj
shaderMore.exe: CMakeFiles/shaderMore.dir/build.make
shaderMore.exe: CMakeFiles/shaderMore.dir/linklibs.rsp
shaderMore.exe: CMakeFiles/shaderMore.dir/objects1.rsp
shaderMore.exe: CMakeFiles/shaderMore.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="F:\project\web learnopengl\shaderMore\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable shaderMore.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\shaderMore.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/shaderMore.dir/build: shaderMore.exe

.PHONY : CMakeFiles/shaderMore.dir/build

CMakeFiles/shaderMore.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\shaderMore.dir\cmake_clean.cmake
.PHONY : CMakeFiles/shaderMore.dir/clean

CMakeFiles/shaderMore.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "F:\project\web learnopengl\shaderMore" "F:\project\web learnopengl\shaderMore" "F:\project\web learnopengl\shaderMore\cmake-build-debug" "F:\project\web learnopengl\shaderMore\cmake-build-debug" "F:\project\web learnopengl\shaderMore\cmake-build-debug\CMakeFiles\shaderMore.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/shaderMore.dir/depend

