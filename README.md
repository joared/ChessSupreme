# ChessSupreme

## Setup Visual studio code project
Ctrl + P -> CMake: Configure.
Should be done when modifying CMakeLists.txt.

## Build the project

### Using cmake
1. Create a "build" directory
2. CD into the "build" directory
3. In terminal: cmake ../

### Using Visual Studio Code
Ctrl + Shift + P -> CMake: build

## Run
1. CD into ChessSupreme/build
2. In terminal: ./ChessSupreme

## Some references
https://www.chessprogramming.org  
https://alexanderameye.github.io/notes/chess-engine/ 
https://github.com/official-stockfish/Stockfish

## Google test
### Install dependencies
sudo apt-get install libgtest-dev  
https://www.eriksmistad.no/getting-started-with-google-test-on-ubuntu/ 
### Create a new test.cpp
- Add .cpp test file in test/
- Add the new .cpp to TESTS in CMakeLists.txt
- Rebuild the project and run SupremeTests
