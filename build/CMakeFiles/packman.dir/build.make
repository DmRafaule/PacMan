# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_SOURCE_DIR = /home/dimond/Projects/Repositories/PacMan

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dimond/Projects/Repositories/PacMan/build

# Include any dependencies generated for this target.
include CMakeFiles/packman.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/packman.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/packman.dir/flags.make

CMakeFiles/packman.dir/src/ghost.cpp.o: CMakeFiles/packman.dir/flags.make
CMakeFiles/packman.dir/src/ghost.cpp.o: ../src/ghost.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dimond/Projects/Repositories/PacMan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/packman.dir/src/ghost.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/packman.dir/src/ghost.cpp.o -c /home/dimond/Projects/Repositories/PacMan/src/ghost.cpp

CMakeFiles/packman.dir/src/ghost.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/packman.dir/src/ghost.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dimond/Projects/Repositories/PacMan/src/ghost.cpp > CMakeFiles/packman.dir/src/ghost.cpp.i

CMakeFiles/packman.dir/src/ghost.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/packman.dir/src/ghost.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dimond/Projects/Repositories/PacMan/src/ghost.cpp -o CMakeFiles/packman.dir/src/ghost.cpp.s

CMakeFiles/packman.dir/src/main.cpp.o: CMakeFiles/packman.dir/flags.make
CMakeFiles/packman.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dimond/Projects/Repositories/PacMan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/packman.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/packman.dir/src/main.cpp.o -c /home/dimond/Projects/Repositories/PacMan/src/main.cpp

CMakeFiles/packman.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/packman.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dimond/Projects/Repositories/PacMan/src/main.cpp > CMakeFiles/packman.dir/src/main.cpp.i

CMakeFiles/packman.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/packman.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dimond/Projects/Repositories/PacMan/src/main.cpp -o CMakeFiles/packman.dir/src/main.cpp.s

CMakeFiles/packman.dir/src/map.cpp.o: CMakeFiles/packman.dir/flags.make
CMakeFiles/packman.dir/src/map.cpp.o: ../src/map.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dimond/Projects/Repositories/PacMan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/packman.dir/src/map.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/packman.dir/src/map.cpp.o -c /home/dimond/Projects/Repositories/PacMan/src/map.cpp

CMakeFiles/packman.dir/src/map.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/packman.dir/src/map.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dimond/Projects/Repositories/PacMan/src/map.cpp > CMakeFiles/packman.dir/src/map.cpp.i

CMakeFiles/packman.dir/src/map.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/packman.dir/src/map.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dimond/Projects/Repositories/PacMan/src/map.cpp -o CMakeFiles/packman.dir/src/map.cpp.s

CMakeFiles/packman.dir/src/menu.cpp.o: CMakeFiles/packman.dir/flags.make
CMakeFiles/packman.dir/src/menu.cpp.o: ../src/menu.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dimond/Projects/Repositories/PacMan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/packman.dir/src/menu.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/packman.dir/src/menu.cpp.o -c /home/dimond/Projects/Repositories/PacMan/src/menu.cpp

CMakeFiles/packman.dir/src/menu.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/packman.dir/src/menu.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dimond/Projects/Repositories/PacMan/src/menu.cpp > CMakeFiles/packman.dir/src/menu.cpp.i

CMakeFiles/packman.dir/src/menu.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/packman.dir/src/menu.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dimond/Projects/Repositories/PacMan/src/menu.cpp -o CMakeFiles/packman.dir/src/menu.cpp.s

CMakeFiles/packman.dir/src/pack.cpp.o: CMakeFiles/packman.dir/flags.make
CMakeFiles/packman.dir/src/pack.cpp.o: ../src/pack.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dimond/Projects/Repositories/PacMan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/packman.dir/src/pack.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/packman.dir/src/pack.cpp.o -c /home/dimond/Projects/Repositories/PacMan/src/pack.cpp

CMakeFiles/packman.dir/src/pack.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/packman.dir/src/pack.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dimond/Projects/Repositories/PacMan/src/pack.cpp > CMakeFiles/packman.dir/src/pack.cpp.i

CMakeFiles/packman.dir/src/pack.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/packman.dir/src/pack.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dimond/Projects/Repositories/PacMan/src/pack.cpp -o CMakeFiles/packman.dir/src/pack.cpp.s

CMakeFiles/packman.dir/src/pack_E.cpp.o: CMakeFiles/packman.dir/flags.make
CMakeFiles/packman.dir/src/pack_E.cpp.o: ../src/pack_E.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dimond/Projects/Repositories/PacMan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/packman.dir/src/pack_E.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/packman.dir/src/pack_E.cpp.o -c /home/dimond/Projects/Repositories/PacMan/src/pack_E.cpp

CMakeFiles/packman.dir/src/pack_E.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/packman.dir/src/pack_E.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dimond/Projects/Repositories/PacMan/src/pack_E.cpp > CMakeFiles/packman.dir/src/pack_E.cpp.i

CMakeFiles/packman.dir/src/pack_E.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/packman.dir/src/pack_E.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dimond/Projects/Repositories/PacMan/src/pack_E.cpp -o CMakeFiles/packman.dir/src/pack_E.cpp.s

CMakeFiles/packman.dir/src/world.cpp.o: CMakeFiles/packman.dir/flags.make
CMakeFiles/packman.dir/src/world.cpp.o: ../src/world.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dimond/Projects/Repositories/PacMan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/packman.dir/src/world.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/packman.dir/src/world.cpp.o -c /home/dimond/Projects/Repositories/PacMan/src/world.cpp

CMakeFiles/packman.dir/src/world.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/packman.dir/src/world.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dimond/Projects/Repositories/PacMan/src/world.cpp > CMakeFiles/packman.dir/src/world.cpp.i

CMakeFiles/packman.dir/src/world.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/packman.dir/src/world.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dimond/Projects/Repositories/PacMan/src/world.cpp -o CMakeFiles/packman.dir/src/world.cpp.s

# Object files for target packman
packman_OBJECTS = \
"CMakeFiles/packman.dir/src/ghost.cpp.o" \
"CMakeFiles/packman.dir/src/main.cpp.o" \
"CMakeFiles/packman.dir/src/map.cpp.o" \
"CMakeFiles/packman.dir/src/menu.cpp.o" \
"CMakeFiles/packman.dir/src/pack.cpp.o" \
"CMakeFiles/packman.dir/src/pack_E.cpp.o" \
"CMakeFiles/packman.dir/src/world.cpp.o"

# External object files for target packman
packman_EXTERNAL_OBJECTS =

packman: CMakeFiles/packman.dir/src/ghost.cpp.o
packman: CMakeFiles/packman.dir/src/main.cpp.o
packman: CMakeFiles/packman.dir/src/map.cpp.o
packman: CMakeFiles/packman.dir/src/menu.cpp.o
packman: CMakeFiles/packman.dir/src/pack.cpp.o
packman: CMakeFiles/packman.dir/src/pack_E.cpp.o
packman: CMakeFiles/packman.dir/src/world.cpp.o
packman: CMakeFiles/packman.dir/build.make
packman: ../dep/SFML/lib/libsfml-audio.so.2.5.1
packman: ../dep/SFML/lib/libsfml-graphics.so.2.5.1
packman: ../dep/SFML/lib/libsfml-network.so.2.5.1
packman: ../dep/SFML/lib/libsfml-system.so.2.5.1
packman: ../dep/SFML/lib/libsfml-window.so.2.5.1
packman: CMakeFiles/packman.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dimond/Projects/Repositories/PacMan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable packman"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/packman.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/packman.dir/build: packman

.PHONY : CMakeFiles/packman.dir/build

CMakeFiles/packman.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/packman.dir/cmake_clean.cmake
.PHONY : CMakeFiles/packman.dir/clean

CMakeFiles/packman.dir/depend:
	cd /home/dimond/Projects/Repositories/PacMan/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dimond/Projects/Repositories/PacMan /home/dimond/Projects/Repositories/PacMan /home/dimond/Projects/Repositories/PacMan/build /home/dimond/Projects/Repositories/PacMan/build /home/dimond/Projects/Repositories/PacMan/build/CMakeFiles/packman.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/packman.dir/depend

