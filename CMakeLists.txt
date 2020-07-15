cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

# Define a project.
project(YarpKinFu LANGUAGES CXX)

# Hard dependencies.
find_package(YCM 0.11 REQUIRED)
find_package(YARP 3.3 REQUIRED COMPONENTS os dev sig)
find_package(OpenCV 4.0 REQUIRED COMPONENTS rgbd)

# Standard installation directories.
include(GNUInstallDirs)

# Control where libraries and executables are placed during the build.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

# Add main contents.
add_subdirectory(src)

# Configure and create uninstall target.
include(AddUninstallTarget)
