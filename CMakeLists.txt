cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

# Define a project.
project(YarpKinFu LANGUAGES CXX)

# Pick up custom CMake modules.
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# Hard dependencies.
find_package(YARP 3.2 REQUIRED COMPONENTS OS dev sig)
find_package(KinectFusionLib REQUIRED)

# Always build YARP devices as MODULE libraries.
set(YARP_FORCE_DYNAMIC_PLUGINS TRUE CACHE INTERNAL "Force dynamic plugins")

# Configure installation paths for YARP resources.
yarp_configure_external_installation(yarp-kinfu WITH_PLUGINS)

# Standard installation directories.
include(GNUInstallDirs)

# Control where libraries and executables are placed during the build.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})

# Create targets if specific requirements are satisfied.
include(CMakeDependentOption)

# Add main contents.
add_subdirectory(programs)

# Configure and create uninstall target.
include(AddUninstallTarget)
