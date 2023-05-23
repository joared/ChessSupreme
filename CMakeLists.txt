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
    ${SRC_DIR}/chesshandler.cpp
    ${SRC_DIR}/bitboard.cpp
    ${SRC_DIR}/move.cpp 
    ${SRC_DIR}/movegen.cpp
    ${SRC_DIR}/piece.cpp 
    ${SRC_DIR}/position.cpp 
    ${SRC_DIR}/utility.cpp
)

# Add the executable
add_executable(ChessSupreme ${SRC_DIR}/${SRC_MAIN} ${SOURCES})
# Add include folder as a private include directory for ChessSupreme
target_include_directories(ChessSupreme
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Add a library to easy link test cases
add_library(SupremeLib STATIC ${SOURCES})
# Add include folder as a private include directory for SupremeLib
target_include_directories(SupremeLib
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# If the project depends on other libraries
# target_link_libraries(ChessSupreme stdc++fs)

if (UNIX)
    set(INSTALL_DIR "~/Desktop/ChessSupremeApplication")
elseif(WIN32)
    set(INSTALL_DIR "C:/Program Files/ChessSupremeApplication")
endif()

set_target_properties(ChessSupreme PROPERTIES OUTPUT_NAME "ChessSupremeConsoleApplication")
# Install the executable to the specified location

install(TARGETS ChessSupreme DESTINATION ${INSTALL_DIR})

# Check if the BUILD_TESTS flag is set
set(BUILD_TESTS True)
# Add a CMake option to enable/disable the optional test
# NOTE: if you wanna change the option, you have to remove the build folder and rebuild the project
option(RUN_OPTIONAL_PERFORMANCE_TEST "Enable optional performance tests" ON)
if(BUILD_TESTS)
    # This is needed to install the test executable (dynamic linking)
    set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)

    set(TEST_MAIN tests.cpp)
    set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)
    set(TESTS 
        ${TEST_DIR}/bitboard_test.cpp
        ${TEST_DIR}/move_test.cpp
        ${TEST_DIR}/perft_test.cpp
        ${TEST_DIR}/piece_test.cpp
        ${TEST_DIR}/position_test.cpp
        ${TEST_DIR}/utility_test.cpp
        )
    # Executable for tests, linking to library
    add_executable(SupremeTests ${TEST_DIR}/${TEST_MAIN} ${TESTS})
    target_link_libraries(SupremeTests SupremeLib)

    # Filter the tests based on the option
    if (RUN_OPTIONAL_PERFORMANCE_TEST)
        target_compile_definitions(SupremeTests PRIVATE RUN_OPTIONAL_PERFORMANCE_TEST)
    endif()

    # Executable for tests, directly from source files
    # add_executable(SupremeTests ${TEST_DIR}/${TEST_MAIN} ${TESTS} ${SOURCES})
    # target_include_directories(SupremeTests
    #     PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
    # )

    # Locate GTest
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})

    target_link_libraries(SupremeTests ${GTEST_LIBRARIES} pthread)
    # Link the test executable with Google Test
    target_link_libraries(SupremeTests gtest_main)
    
    # Add the test executable to CTest
    include(GoogleTest)
    gtest_discover_tests(SupremeTests)

    # Install the test executable
    install(TARGETS SupremeTests DESTINATION ${INSTALL_DIR})

    ### Interactive tests ###
    # Test pseudo moves for pieces interactively
    add_executable(TestPseudoAttacksInteractive ${TEST_DIR}/test_pseudoattacks_interactive.cpp)
    target_link_libraries(TestPseudoAttacksInteractive SupremeLib)

    # Test bitshifts interactively
    add_executable(TestBitshiftInteractive ${TEST_DIR}/test_bitshift_interactive.cpp)
    target_link_libraries(TestBitshiftInteractive SupremeLib)

endif()
