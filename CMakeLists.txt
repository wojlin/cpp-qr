# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(CPP_QR VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add Google Test
set(GTEST_ROOT ${CMAKE_SOURCE_DIR}/external/googletest)
set(gtest_discover_tests_multi_config TRUE)
add_subdirectory(${GTEST_ROOT} ${CMAKE_BINARY_DIR}/gtest)

# Main include directories
include_directories(include)

# Create a library from the source files
file(GLOB SOURCES "src/*.cpp")
add_library(${PROJECT_NAME}_lib ${SOURCES})

# Link Google Test with the library
target_link_libraries(${PROJECT_NAME}_lib gtest gmock)

# Create the main executable (optional if you have a main executable separate from tests)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_lib)

# Add your tests
enable_testing()
file(GLOB TEST_SOURCES "test/unit/*.cpp")
# Loop through each test file and add it as an executable and register it with CTest
foreach(TEST_SRC ${TEST_SOURCES})
    # Extract the name of the test without the directory or file extension
    get_filename_component(TEST_NAME ${TEST_SRC} NAME_WE)
    
    # Add each test as an executable
    add_executable(${TEST_NAME} ${TEST_SRC})
    
    # Link libraries to each test executable
    target_link_libraries(${TEST_NAME} ${PROJECT_NAME}_lib gtest gmock)
    
    # Register each test with CTest
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()

message(STATUS "Test files: ${TEST_SOURCES}")
