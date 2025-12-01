@echo off
REM Build and run the separation test on Windows (cmd.exe)
REM Usage: double-click or run from separation\ directory.












pauseendlocal%OUT%echo Running %OUT% ...)  goto :EOF  echo Compilation failed.if errorlevel 1 (set SRC_FILES=City.cpp Route.cpp MinHeap.cpp Graph.cpp test.cpp
nset OUT=separation_test.exe
n
necho Compiling %SRC_FILES% ...
ng++ -std=c++17 %SRC_FILES% -o %OUT%nsetlocal