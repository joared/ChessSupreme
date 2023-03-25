cmake_minimum_required(VERSION 3.10)

# Set the compiler to g++
set(CMAKE_CXX_COMPILER "g++")

# Set the C++ standard to C++17. Necessary flags are automatically set to the g++ compiler
set(CMAKE_CXX_STANDARD 17)

# Set the flags for the compiler
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
# add any other flags as needed

# Define the project. Can be used to modify the behaviour of the build.
project(ChessSupreme VERSION 1.0.0 DESCRIPTION "The ChessSupreme engine!")

# Define the path to the main source file
set(SRC_MAIN main.cpp)

# Define the path to the source directory
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Add the main source file to the executable
add_executable(ChessSupreme ${SRC_DIR}/${SRC_MAIN} ${SRC_DIR}/board.cpp ${SRC_DIR}/piece.cpp ${SRC_DIR}/move.cpp ${SRC_DIR}/utility.cpp)

# Add include folder as a private include directory for ChessSupreme
target_include_directories(ChessSupreme
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# If the project depends on other libraries
# target_link_libraries(ChessSupreme stdc++fs)
