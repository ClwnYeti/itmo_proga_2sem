# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.2.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.2.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\crazy\CLionProjects\itmo_proga_2sem\2sem3lab

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\crazy\CLionProjects\itmo_proga_2sem\2sem3lab\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/2sem3lab.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/2sem3lab.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/2sem3lab.dir/flags.make

CMakeFiles/2sem3lab.dir/main.cpp.obj: CMakeFiles/2sem3lab.dir/flags.make
CMakeFiles/2sem3lab.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\crazy\CLionProjects\itmo_proga_2sem\2sem3lab\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/2sem3lab.dir/main.cpp.obj"
	C:\Users\crazy\gcc\bin\c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\2sem3lab.dir\main.cpp.obj -c C:\Users\crazy\CLionProjects\itmo_proga_2sem\2sem3lab\main.cpp

CMakeFiles/2sem3lab.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/2sem3lab.dir/main.cpp.i"
	C:\Users\crazy\gcc\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\crazy\CLionProjects\itmo_proga_2sem\2sem3lab\main.cpp > CMakeFiles\2sem3lab.dir\main.cpp.i

CMakeFiles/2sem3lab.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/2sem3lab.dir/main.cpp.s"
	C:\Users\crazy\gcc\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\crazy\CLionProjects\itmo_proga_2sem\2sem3lab\main.cpp -o CMakeFiles\2sem3lab.dir\main.cpp.s

CMakeFiles/2sem3lab.dir/pugixml.cpp.obj: CMakeFiles/2sem3lab.dir/flags.make
CMakeFiles/2sem3lab.dir/pugixml.cpp.obj: ../pugixml.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\crazy\CLionProjects\itmo_proga_2sem\2sem3lab\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/2sem3lab.dir/pugixml.cpp.obj"
	C:\Users\crazy\gcc\bin\c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\2sem3lab.dir\pugixml.cpp.obj -c C:\Users\crazy\CLionProjects\itmo_proga_2sem\2sem3lab\pugixml.cpp

CMakeFiles/2sem3lab.dir/pugixml.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/2sem3lab.dir/pugixml.cpp.i"
	C:\Users\crazy\gcc\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\crazy\CLionProjects\itmo_proga_2sem\2sem3lab\pugixml.cpp > CMakeFiles\2sem3lab.dir\pugixml.cpp.i

CMakeFiles/2sem3lab.dir/pugixml.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/2sem3lab.dir/pugixml.cpp.s"
	C:\Users\crazy\gcc\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\crazy\CLionProjects\itmo_proga_2sem\2sem3lab\pugixml.cpp -o CMakeFiles\2sem3lab.dir\pugixml.cpp.s

# Object files for target 2sem3lab
2sem3lab_OBJECTS = \
"CMakeFiles/2sem3lab.dir/main.cpp.obj" \
"CMakeFiles/2sem3lab.dir/pugixml.cpp.obj"

# External object files for target 2sem3lab
2sem3lab_EXTERNAL_OBJECTS =

2sem3lab.exe: CMakeFiles/2sem3lab.dir/main.cpp.obj
2sem3lab.exe: CMakeFiles/2sem3lab.dir/pugixml.cpp.obj
2sem3lab.exe: CMakeFiles/2sem3lab.dir/build.make
2sem3lab.exe: CMakeFiles/2sem3lab.dir/linklibs.rsp
2sem3lab.exe: CMakeFiles/2sem3lab.dir/objects1.rsp
2sem3lab.exe: CMakeFiles/2sem3lab.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\crazy\CLionProjects\itmo_proga_2sem\2sem3lab\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable 2sem3lab.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\2sem3lab.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/2sem3lab.dir/build: 2sem3lab.exe

.PHONY : CMakeFiles/2sem3lab.dir/build

CMakeFiles/2sem3lab.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\2sem3lab.dir\cmake_clean.cmake
.PHONY : CMakeFiles/2sem3lab.dir/clean

CMakeFiles/2sem3lab.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\crazy\CLionProjects\itmo_proga_2sem\2sem3lab C:\Users\crazy\CLionProjects\itmo_proga_2sem\2sem3lab C:\Users\crazy\CLionProjects\itmo_proga_2sem\2sem3lab\cmake-build-debug C:\Users\crazy\CLionProjects\itmo_proga_2sem\2sem3lab\cmake-build-debug C:\Users\crazy\CLionProjects\itmo_proga_2sem\2sem3lab\cmake-build-debug\CMakeFiles\2sem3lab.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/2sem3lab.dir/depend

