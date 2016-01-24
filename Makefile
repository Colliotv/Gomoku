# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.4

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /home/collio_v/rendu/Gomoku

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/collio_v/rendu/Gomoku

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/collio_v/rendu/Gomoku/CMakeFiles /home/collio_v/rendu/Gomoku/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/collio_v/rendu/Gomoku/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named Gomoku

# Build rule for target.
Gomoku: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 Gomoku
.PHONY : Gomoku

# fast build rule for target.
Gomoku/fast:
	$(MAKE) -f CMakeFiles/Gomoku.dir/build.make CMakeFiles/Gomoku.dir/build
.PHONY : Gomoku/fast

src/IAminmax/IAminmax.o: src/IAminmax/IAminmax.cpp.o

.PHONY : src/IAminmax/IAminmax.o

# target to build an object file
src/IAminmax/IAminmax.cpp.o:
	$(MAKE) -f CMakeFiles/Gomoku.dir/build.make CMakeFiles/Gomoku.dir/src/IAminmax/IAminmax.cpp.o
.PHONY : src/IAminmax/IAminmax.cpp.o

src/IAminmax/IAminmax.i: src/IAminmax/IAminmax.cpp.i

.PHONY : src/IAminmax/IAminmax.i

# target to preprocess a source file
src/IAminmax/IAminmax.cpp.i:
	$(MAKE) -f CMakeFiles/Gomoku.dir/build.make CMakeFiles/Gomoku.dir/src/IAminmax/IAminmax.cpp.i
.PHONY : src/IAminmax/IAminmax.cpp.i

src/IAminmax/IAminmax.s: src/IAminmax/IAminmax.cpp.s

.PHONY : src/IAminmax/IAminmax.s

# target to generate assembly for a file
src/IAminmax/IAminmax.cpp.s:
	$(MAKE) -f CMakeFiles/Gomoku.dir/build.make CMakeFiles/Gomoku.dir/src/IAminmax/IAminmax.cpp.s
.PHONY : src/IAminmax/IAminmax.cpp.s

src/game/Player.o: src/game/Player.cpp.o

.PHONY : src/game/Player.o

# target to build an object file
src/game/Player.cpp.o:
	$(MAKE) -f CMakeFiles/Gomoku.dir/build.make CMakeFiles/Gomoku.dir/src/game/Player.cpp.o
.PHONY : src/game/Player.cpp.o

src/game/Player.i: src/game/Player.cpp.i

.PHONY : src/game/Player.i

# target to preprocess a source file
src/game/Player.cpp.i:
	$(MAKE) -f CMakeFiles/Gomoku.dir/build.make CMakeFiles/Gomoku.dir/src/game/Player.cpp.i
.PHONY : src/game/Player.cpp.i

src/game/Player.s: src/game/Player.cpp.s

.PHONY : src/game/Player.s

# target to generate assembly for a file
src/game/Player.cpp.s:
	$(MAKE) -f CMakeFiles/Gomoku.dir/build.make CMakeFiles/Gomoku.dir/src/game/Player.cpp.s
.PHONY : src/game/Player.cpp.s

src/graphics/sfml.o: src/graphics/sfml.cpp.o

.PHONY : src/graphics/sfml.o

# target to build an object file
src/graphics/sfml.cpp.o:
	$(MAKE) -f CMakeFiles/Gomoku.dir/build.make CMakeFiles/Gomoku.dir/src/graphics/sfml.cpp.o
.PHONY : src/graphics/sfml.cpp.o

src/graphics/sfml.i: src/graphics/sfml.cpp.i

.PHONY : src/graphics/sfml.i

# target to preprocess a source file
src/graphics/sfml.cpp.i:
	$(MAKE) -f CMakeFiles/Gomoku.dir/build.make CMakeFiles/Gomoku.dir/src/graphics/sfml.cpp.i
.PHONY : src/graphics/sfml.cpp.i

src/graphics/sfml.s: src/graphics/sfml.cpp.s

.PHONY : src/graphics/sfml.s

# target to generate assembly for a file
src/graphics/sfml.cpp.s:
	$(MAKE) -f CMakeFiles/Gomoku.dir/build.make CMakeFiles/Gomoku.dir/src/graphics/sfml.cpp.s
.PHONY : src/graphics/sfml.cpp.s

src/referee/Board.o: src/referee/Board.cpp.o

.PHONY : src/referee/Board.o

# target to build an object file
src/referee/Board.cpp.o:
	$(MAKE) -f CMakeFiles/Gomoku.dir/build.make CMakeFiles/Gomoku.dir/src/referee/Board.cpp.o
.PHONY : src/referee/Board.cpp.o

src/referee/Board.i: src/referee/Board.cpp.i

.PHONY : src/referee/Board.i

# target to preprocess a source file
src/referee/Board.cpp.i:
	$(MAKE) -f CMakeFiles/Gomoku.dir/build.make CMakeFiles/Gomoku.dir/src/referee/Board.cpp.i
.PHONY : src/referee/Board.cpp.i

src/referee/Board.s: src/referee/Board.cpp.s

.PHONY : src/referee/Board.s

# target to generate assembly for a file
src/referee/Board.cpp.s:
	$(MAKE) -f CMakeFiles/Gomoku.dir/build.make CMakeFiles/Gomoku.dir/src/referee/Board.cpp.s
.PHONY : src/referee/Board.cpp.s

src/referee/Piece.o: src/referee/Piece.cpp.o

.PHONY : src/referee/Piece.o

# target to build an object file
src/referee/Piece.cpp.o:
	$(MAKE) -f CMakeFiles/Gomoku.dir/build.make CMakeFiles/Gomoku.dir/src/referee/Piece.cpp.o
.PHONY : src/referee/Piece.cpp.o

src/referee/Piece.i: src/referee/Piece.cpp.i

.PHONY : src/referee/Piece.i

# target to preprocess a source file
src/referee/Piece.cpp.i:
	$(MAKE) -f CMakeFiles/Gomoku.dir/build.make CMakeFiles/Gomoku.dir/src/referee/Piece.cpp.i
.PHONY : src/referee/Piece.cpp.i

src/referee/Piece.s: src/referee/Piece.cpp.s

.PHONY : src/referee/Piece.s

# target to generate assembly for a file
src/referee/Piece.cpp.s:
	$(MAKE) -f CMakeFiles/Gomoku.dir/build.make CMakeFiles/Gomoku.dir/src/referee/Piece.cpp.s
.PHONY : src/referee/Piece.cpp.s

src/referee/Referee.o: src/referee/Referee.cpp.o

.PHONY : src/referee/Referee.o

# target to build an object file
src/referee/Referee.cpp.o:
	$(MAKE) -f CMakeFiles/Gomoku.dir/build.make CMakeFiles/Gomoku.dir/src/referee/Referee.cpp.o
.PHONY : src/referee/Referee.cpp.o

src/referee/Referee.i: src/referee/Referee.cpp.i

.PHONY : src/referee/Referee.i

# target to preprocess a source file
src/referee/Referee.cpp.i:
	$(MAKE) -f CMakeFiles/Gomoku.dir/build.make CMakeFiles/Gomoku.dir/src/referee/Referee.cpp.i
.PHONY : src/referee/Referee.cpp.i

src/referee/Referee.s: src/referee/Referee.cpp.s

.PHONY : src/referee/Referee.s

# target to generate assembly for a file
src/referee/Referee.cpp.s:
	$(MAKE) -f CMakeFiles/Gomoku.dir/build.make CMakeFiles/Gomoku.dir/src/referee/Referee.cpp.s
.PHONY : src/referee/Referee.cpp.s

src/start/main.o: src/start/main.cpp.o

.PHONY : src/start/main.o

# target to build an object file
src/start/main.cpp.o:
	$(MAKE) -f CMakeFiles/Gomoku.dir/build.make CMakeFiles/Gomoku.dir/src/start/main.cpp.o
.PHONY : src/start/main.cpp.o

src/start/main.i: src/start/main.cpp.i

.PHONY : src/start/main.i

# target to preprocess a source file
src/start/main.cpp.i:
	$(MAKE) -f CMakeFiles/Gomoku.dir/build.make CMakeFiles/Gomoku.dir/src/start/main.cpp.i
.PHONY : src/start/main.cpp.i

src/start/main.s: src/start/main.cpp.s

.PHONY : src/start/main.s

# target to generate assembly for a file
src/start/main.cpp.s:
	$(MAKE) -f CMakeFiles/Gomoku.dir/build.make CMakeFiles/Gomoku.dir/src/start/main.cpp.s
.PHONY : src/start/main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... Gomoku"
	@echo "... src/IAminmax/IAminmax.o"
	@echo "... src/IAminmax/IAminmax.i"
	@echo "... src/IAminmax/IAminmax.s"
	@echo "... src/game/Player.o"
	@echo "... src/game/Player.i"
	@echo "... src/game/Player.s"
	@echo "... src/graphics/sfml.o"
	@echo "... src/graphics/sfml.i"
	@echo "... src/graphics/sfml.s"
	@echo "... src/referee/Board.o"
	@echo "... src/referee/Board.i"
	@echo "... src/referee/Board.s"
	@echo "... src/referee/Piece.o"
	@echo "... src/referee/Piece.i"
	@echo "... src/referee/Piece.s"
	@echo "... src/referee/Referee.o"
	@echo "... src/referee/Referee.i"
	@echo "... src/referee/Referee.s"
	@echo "... src/start/main.o"
	@echo "... src/start/main.i"
	@echo "... src/start/main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

