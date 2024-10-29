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
include_directories(${GTEST_ROOT}/googletest/include ${GTEST_ROOT}/googlemock/include)
add_subdirectory(${GTEST_ROOT} ${CMAKE_BINARY_DIR}/gtest)

# Include directories
include_directories(include)

# Source files
file(GLOB SOURCES "src/*.cpp")

# Executable target
add_executable(${PROJECT_NAME} ${SOURCES})

# Link Google Test
target_link_libraries(CPP_QR gtest gmock)

# Add your tests
enable_testing()
add_executable(QRModeTests "test/test_qr_mode_selector.cpp")
target_link_libraries(QRModeTests gtest gmock)
add_test(NAME QRModeTests COMMAND QRModeTests)