# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.0.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.0.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/halfdan-rump/projects/satoyama/satoyama-edge/aggregator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/halfdan-rump/projects/satoyama/satoyama-edge/aggregator/build

# Include any dependencies generated for this target.
include CMakeFiles/freakduino-lr_chibiArduino.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/freakduino-lr_chibiArduino.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/freakduino-lr_chibiArduino.dir/flags.make

CMakeFiles/freakduino-lr_chibiArduino.dir/Users/halfdan-rump/Documents/Arduino/libraries/chibiArduino/chibi.cpp.obj: CMakeFiles/freakduino-lr_chibiArduino.dir/flags.make
CMakeFiles/freakduino-lr_chibiArduino.dir/Users/halfdan-rump/Documents/Arduino/libraries/chibiArduino/chibi.cpp.obj: /Users/halfdan-rump/Documents/Arduino/libraries/chibiArduino/chibi.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/halfdan-rump/projects/satoyama/satoyama-edge/aggregator/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/freakduino-lr_chibiArduino.dir/Users/halfdan-rump/Documents/Arduino/libraries/chibiArduino/chibi.cpp.obj"
	/usr/local/CrossPack-AVR/bin/avr-g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/freakduino-lr_chibiArduino.dir/Users/halfdan-rump/Documents/Arduino/libraries/chibiArduino/chibi.cpp.obj -c /Users/halfdan-rump/Documents/Arduino/libraries/chibiArduino/chibi.cpp

CMakeFiles/freakduino-lr_chibiArduino.dir/Users/halfdan-rump/Documents/Arduino/libraries/chibiArduino/chibi.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/freakduino-lr_chibiArduino.dir/Users/halfdan-rump/Documents/Arduino/libraries/chibiArduino/chibi.cpp.i"
	/usr/local/CrossPack-AVR/bin/avr-g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/halfdan-rump/Documents/Arduino/libraries/chibiArduino/chibi.cpp > CMakeFiles/freakduino-lr_chibiArduino.dir/Users/halfdan-rump/Documents/Arduino/libraries/chibiArduino/chibi.cpp.i

CMakeFiles/freakduino-lr_chibiArduino.dir/Users/halfdan-rump/Documents/Arduino/libraries/chibiArduino/chibi.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/freakduino-lr_chibiArduino.dir/Users/halfdan-rump/Documents/Arduino/libraries/chibiArduino/chibi.cpp.s"
	/usr/local/CrossPack-AVR/bin/avr-g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/halfdan-rump/Documents/Arduino/libraries/chibiArduino/chibi.cpp -o CMakeFiles/freakduino-lr_chibiArduino.dir/Users/halfdan-rump/Documents/Arduino/libraries/chibiArduino/chibi.cpp.s

CMakeFiles/freakduino-lr_chibiArduino.dir/Users/halfdan-rump/Documents/Arduino/libraries/chibiArduino/chibi.cpp.obj.requires:
.PHONY : CMakeFiles/freakduino-lr_chibiArduino.dir/Users/halfdan-rump/Documents/Arduino/libraries/chibiArduino/chibi.cpp.obj.requires

CMakeFiles/freakduino-lr_chibiArduino.dir/Users/halfdan-rump/Documents/Arduino/libraries/chibiArduino/chibi.cpp.obj.provides: CMakeFiles/freakduino-lr_chibiArduino.dir/Users/halfdan-rump/Documents/Arduino/libraries/chibiArduino/chibi.cpp.obj.requires
	$(MAKE) -f CMakeFiles/freakduino-lr_chibiArduino.dir/build.make CMakeFiles/freakduino-lr_chibiArduino.dir/Users/halfdan-rump/Documents/Arduino/libraries/chibiArduino/chibi.cpp.obj.provides.build
.PHONY : CMakeFiles/freakduino-lr_chibiArduino.dir/Users/halfdan-rump/Documents/Arduino/libraries/chibiArduino/chibi.cpp.obj.provides

CMakeFiles/freakduino-lr_chibiArduino.dir/Users/halfdan-rump/Documents/Arduino/libraries/chibiArduino/chibi.cpp.obj.provides.build: CMakeFiles/freakduino-lr_chibiArduino.dir/Users/halfdan-rump/Documents/Arduino/libraries/chibiArduino/chibi.cpp.obj

# Object files for target freakduino-lr_chibiArduino
freakduino__lr_chibiArduino_OBJECTS = \
"CMakeFiles/freakduino-lr_chibiArduino.dir/Users/halfdan-rump/Documents/Arduino/libraries/chibiArduino/chibi.cpp.obj"

# External object files for target freakduino-lr_chibiArduino
freakduino__lr_chibiArduino_EXTERNAL_OBJECTS =

libfreakduino-lr_chibiArduino.a: CMakeFiles/freakduino-lr_chibiArduino.dir/Users/halfdan-rump/Documents/Arduino/libraries/chibiArduino/chibi.cpp.obj
libfreakduino-lr_chibiArduino.a: CMakeFiles/freakduino-lr_chibiArduino.dir/build.make
libfreakduino-lr_chibiArduino.a: CMakeFiles/freakduino-lr_chibiArduino.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libfreakduino-lr_chibiArduino.a"
	$(CMAKE_COMMAND) -P CMakeFiles/freakduino-lr_chibiArduino.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/freakduino-lr_chibiArduino.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/freakduino-lr_chibiArduino.dir/build: libfreakduino-lr_chibiArduino.a
.PHONY : CMakeFiles/freakduino-lr_chibiArduino.dir/build

CMakeFiles/freakduino-lr_chibiArduino.dir/requires: CMakeFiles/freakduino-lr_chibiArduino.dir/Users/halfdan-rump/Documents/Arduino/libraries/chibiArduino/chibi.cpp.obj.requires
.PHONY : CMakeFiles/freakduino-lr_chibiArduino.dir/requires

CMakeFiles/freakduino-lr_chibiArduino.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/freakduino-lr_chibiArduino.dir/cmake_clean.cmake
.PHONY : CMakeFiles/freakduino-lr_chibiArduino.dir/clean

CMakeFiles/freakduino-lr_chibiArduino.dir/depend:
	cd /Users/halfdan-rump/projects/satoyama/satoyama-edge/aggregator/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/halfdan-rump/projects/satoyama/satoyama-edge/aggregator /Users/halfdan-rump/projects/satoyama/satoyama-edge/aggregator /Users/halfdan-rump/projects/satoyama/satoyama-edge/aggregator/build /Users/halfdan-rump/projects/satoyama/satoyama-edge/aggregator/build /Users/halfdan-rump/projects/satoyama/satoyama-edge/aggregator/build/CMakeFiles/freakduino-lr_chibiArduino.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/freakduino-lr_chibiArduino.dir/depend

