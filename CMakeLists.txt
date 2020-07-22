cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

# Define a project.
project(YarpKinFu LANGUAGES CXX)

# Find hard dependencies.
find_package(YCM 0.11 REQUIRED)
find_package(YARP 3.3 REQUIRED COMPONENTS os dev sig)
find_package(OpenCV 4.0 REQUIRED COMPONENTS core rgbd)
find_package(VTK 6.0 REQUIRED)

# Create variables for standard installation directories.
include(GNUInstallDirs)

# Control where libraries and executables are placed during the build.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

if(VTK_VERSION VERSION_LESS 9.0)
    include(${VTK_USE_FILE})
endif()

# Create executable target.
add_executable(yarp-kinfu src/main.cpp
                          src/YarpKinFu.hpp
                          src/YarpKinFu.cpp
                          src/CloudVisualizer.hpp
                          src/CloudVisualizer.cpp)

# Register dependencies.
target_link_libraries(yarp-kinfu ${YARP_LIBRARIES} ${OpenCV_LIBS} ${VTK_LIBRARIES})

# Set compiler features.
target_compile_features(yarp-kinfu PRIVATE cxx_std_11)

# Register VTK module.
if(VTK_VERSION VERSION_GREATER_EQUAL 9.0)
    vtk_module_autoinit(TARGETS yarp-kinfu MODULES ${VTK_LIBRARIES})
endif()

# Install target.
install(TARGETS yarp-kinfu
        DESTINATION ${CMAKE_INSTALL_BINDIR})

# Configure and create uninstall target.
include(AddUninstallTarget)
