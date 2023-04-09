cmake_minimum_required(VERSION 3.10)

# Set the compiler to g++
set(CMAKE_CXX_COMPILER "g++")

# Set the C++ standard to C++11. Necessary flags are automatically set to the g++ compiler.
set(CMAKE_CXX_STANDARD 11)

# Set the flags for the compiler
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
# add any other flags as needed

# Define the project. Can be used to modify the behaviour of the build.
project(ChessSupreme VERSION 1.0.0 DESCRIPTION "The ChessSupreme engine!")

# Define the path to the main source file
set(SRC_MAIN main.cpp)

# Define the path to the source directory
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# The source files needed to compile the project executable
set(SOURCES 
    ${SRC_DIR}/${SRC_MAIN} 
    ${SRC_DIR}/position.cpp 
    ${SRC_DIR}/bitboard.cpp 
    ${SRC_DIR}/piece.cpp 
    ${SRC_DIR}/move.cpp 
    ${SRC_DIR}/utility.cpp
)

# Add the executable
add_executable(ChessSupreme ${SOURCES})

# Add include folder as a private include directory for ChessSupreme
target_include_directories(ChessSupreme
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# If the project depends on other libraries
# target_link_libraries(ChessSupreme stdc++fs)

# Check if the BUILD_TESTS flag is set
if(BUILD_TESTS)
    set(TEST_MAIN tests.cpp)
    set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)
    set(TESTS 
        ${TEST_DIR}/${TEST_MAIN}
        ${TEST_DIR}/bitboard_test.cpp
        )
    # Add a test executable for the project
    add_executable(SupremeTests ${TESTS})
    
    target_include_directories(SupremeTests
      PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

    # Locate GTest
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})

    target_link_libraries(SupremeTests ${GTEST_LIBRARIES} pthread)
    # Link the test executable with Google Test
    target_link_libraries(SupremeTests gtest_main)
    
    # Add the test executable to CTest
    include(GoogleTest)
    gtest_discover_tests(SupremeTests)
endif()
