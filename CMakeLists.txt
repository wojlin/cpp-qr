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
add_executable(QRModeTests "test/unit/TestQrModeSelector.cpp")
target_link_libraries(QRModeTests ${PROJECT_NAME}_lib gtest gmock)

# Register the tests with CTest
add_test(NAME QRModeTests COMMAND QRModeTests)
