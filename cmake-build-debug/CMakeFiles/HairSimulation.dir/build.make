# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/limpan/Documents/Sidoprojekt/HairSimulation

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/limpan/Documents/Sidoprojekt/HairSimulation/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/HairSimulation.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/HairSimulation.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HairSimulation.dir/flags.make

CMakeFiles/HairSimulation.dir/main.cpp.o: CMakeFiles/HairSimulation.dir/flags.make
CMakeFiles/HairSimulation.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/limpan/Documents/Sidoprojekt/HairSimulation/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/HairSimulation.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HairSimulation.dir/main.cpp.o -c /Users/limpan/Documents/Sidoprojekt/HairSimulation/main.cpp

CMakeFiles/HairSimulation.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HairSimulation.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/limpan/Documents/Sidoprojekt/HairSimulation/main.cpp > CMakeFiles/HairSimulation.dir/main.cpp.i

CMakeFiles/HairSimulation.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HairSimulation.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/limpan/Documents/Sidoprojekt/HairSimulation/main.cpp -o CMakeFiles/HairSimulation.dir/main.cpp.s

CMakeFiles/HairSimulation.dir/src/FileReader.cpp.o: CMakeFiles/HairSimulation.dir/flags.make
CMakeFiles/HairSimulation.dir/src/FileReader.cpp.o: ../src/FileReader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/limpan/Documents/Sidoprojekt/HairSimulation/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/HairSimulation.dir/src/FileReader.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HairSimulation.dir/src/FileReader.cpp.o -c /Users/limpan/Documents/Sidoprojekt/HairSimulation/src/FileReader.cpp

CMakeFiles/HairSimulation.dir/src/FileReader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HairSimulation.dir/src/FileReader.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/limpan/Documents/Sidoprojekt/HairSimulation/src/FileReader.cpp > CMakeFiles/HairSimulation.dir/src/FileReader.cpp.i

CMakeFiles/HairSimulation.dir/src/FileReader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HairSimulation.dir/src/FileReader.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/limpan/Documents/Sidoprojekt/HairSimulation/src/FileReader.cpp -o CMakeFiles/HairSimulation.dir/src/FileReader.cpp.s

CMakeFiles/HairSimulation.dir/src/MeshObject.cpp.o: CMakeFiles/HairSimulation.dir/flags.make
CMakeFiles/HairSimulation.dir/src/MeshObject.cpp.o: ../src/MeshObject.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/limpan/Documents/Sidoprojekt/HairSimulation/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/HairSimulation.dir/src/MeshObject.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HairSimulation.dir/src/MeshObject.cpp.o -c /Users/limpan/Documents/Sidoprojekt/HairSimulation/src/MeshObject.cpp

CMakeFiles/HairSimulation.dir/src/MeshObject.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HairSimulation.dir/src/MeshObject.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/limpan/Documents/Sidoprojekt/HairSimulation/src/MeshObject.cpp > CMakeFiles/HairSimulation.dir/src/MeshObject.cpp.i

CMakeFiles/HairSimulation.dir/src/MeshObject.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HairSimulation.dir/src/MeshObject.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/limpan/Documents/Sidoprojekt/HairSimulation/src/MeshObject.cpp -o CMakeFiles/HairSimulation.dir/src/MeshObject.cpp.s

CMakeFiles/HairSimulation.dir/src/Particle.cpp.o: CMakeFiles/HairSimulation.dir/flags.make
CMakeFiles/HairSimulation.dir/src/Particle.cpp.o: ../src/Particle.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/limpan/Documents/Sidoprojekt/HairSimulation/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/HairSimulation.dir/src/Particle.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HairSimulation.dir/src/Particle.cpp.o -c /Users/limpan/Documents/Sidoprojekt/HairSimulation/src/Particle.cpp

CMakeFiles/HairSimulation.dir/src/Particle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HairSimulation.dir/src/Particle.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/limpan/Documents/Sidoprojekt/HairSimulation/src/Particle.cpp > CMakeFiles/HairSimulation.dir/src/Particle.cpp.i

CMakeFiles/HairSimulation.dir/src/Particle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HairSimulation.dir/src/Particle.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/limpan/Documents/Sidoprojekt/HairSimulation/src/Particle.cpp -o CMakeFiles/HairSimulation.dir/src/Particle.cpp.s

CMakeFiles/HairSimulation.dir/src/ShaderProgram.cpp.o: CMakeFiles/HairSimulation.dir/flags.make
CMakeFiles/HairSimulation.dir/src/ShaderProgram.cpp.o: ../src/ShaderProgram.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/limpan/Documents/Sidoprojekt/HairSimulation/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/HairSimulation.dir/src/ShaderProgram.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HairSimulation.dir/src/ShaderProgram.cpp.o -c /Users/limpan/Documents/Sidoprojekt/HairSimulation/src/ShaderProgram.cpp

CMakeFiles/HairSimulation.dir/src/ShaderProgram.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HairSimulation.dir/src/ShaderProgram.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/limpan/Documents/Sidoprojekt/HairSimulation/src/ShaderProgram.cpp > CMakeFiles/HairSimulation.dir/src/ShaderProgram.cpp.i

CMakeFiles/HairSimulation.dir/src/ShaderProgram.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HairSimulation.dir/src/ShaderProgram.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/limpan/Documents/Sidoprojekt/HairSimulation/src/ShaderProgram.cpp -o CMakeFiles/HairSimulation.dir/src/ShaderProgram.cpp.s

CMakeFiles/HairSimulation.dir/src/Texture.cpp.o: CMakeFiles/HairSimulation.dir/flags.make
CMakeFiles/HairSimulation.dir/src/Texture.cpp.o: ../src/Texture.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/limpan/Documents/Sidoprojekt/HairSimulation/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/HairSimulation.dir/src/Texture.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HairSimulation.dir/src/Texture.cpp.o -c /Users/limpan/Documents/Sidoprojekt/HairSimulation/src/Texture.cpp

CMakeFiles/HairSimulation.dir/src/Texture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HairSimulation.dir/src/Texture.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/limpan/Documents/Sidoprojekt/HairSimulation/src/Texture.cpp > CMakeFiles/HairSimulation.dir/src/Texture.cpp.i

CMakeFiles/HairSimulation.dir/src/Texture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HairSimulation.dir/src/Texture.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/limpan/Documents/Sidoprojekt/HairSimulation/src/Texture.cpp -o CMakeFiles/HairSimulation.dir/src/Texture.cpp.s

# Object files for target HairSimulation
HairSimulation_OBJECTS = \
"CMakeFiles/HairSimulation.dir/main.cpp.o" \
"CMakeFiles/HairSimulation.dir/src/FileReader.cpp.o" \
"CMakeFiles/HairSimulation.dir/src/MeshObject.cpp.o" \
"CMakeFiles/HairSimulation.dir/src/Particle.cpp.o" \
"CMakeFiles/HairSimulation.dir/src/ShaderProgram.cpp.o" \
"CMakeFiles/HairSimulation.dir/src/Texture.cpp.o"

# External object files for target HairSimulation
HairSimulation_EXTERNAL_OBJECTS =

HairSimulation: CMakeFiles/HairSimulation.dir/main.cpp.o
HairSimulation: CMakeFiles/HairSimulation.dir/src/FileReader.cpp.o
HairSimulation: CMakeFiles/HairSimulation.dir/src/MeshObject.cpp.o
HairSimulation: CMakeFiles/HairSimulation.dir/src/Particle.cpp.o
HairSimulation: CMakeFiles/HairSimulation.dir/src/ShaderProgram.cpp.o
HairSimulation: CMakeFiles/HairSimulation.dir/src/Texture.cpp.o
HairSimulation: CMakeFiles/HairSimulation.dir/build.make
HairSimulation: /usr/local/lib/libGLEW.dylib
HairSimulation: external/glfw-3.2.1/src/libglfw3.a
HairSimulation: CMakeFiles/HairSimulation.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/limpan/Documents/Sidoprojekt/HairSimulation/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable HairSimulation"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HairSimulation.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/HairSimulation.dir/build: HairSimulation

.PHONY : CMakeFiles/HairSimulation.dir/build

CMakeFiles/HairSimulation.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/HairSimulation.dir/cmake_clean.cmake
.PHONY : CMakeFiles/HairSimulation.dir/clean

CMakeFiles/HairSimulation.dir/depend:
	cd /Users/limpan/Documents/Sidoprojekt/HairSimulation/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/limpan/Documents/Sidoprojekt/HairSimulation /Users/limpan/Documents/Sidoprojekt/HairSimulation /Users/limpan/Documents/Sidoprojekt/HairSimulation/cmake-build-debug /Users/limpan/Documents/Sidoprojekt/HairSimulation/cmake-build-debug /Users/limpan/Documents/Sidoprojekt/HairSimulation/cmake-build-debug/CMakeFiles/HairSimulation.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/HairSimulation.dir/depend
