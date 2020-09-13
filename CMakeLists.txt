cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

# Define a project.
project(YarpKinFu LANGUAGES CXX)

# Find hard dependencies.
find_package(YCM 0.11 REQUIRED)
find_package(YARP 3.3 REQUIRED COMPONENTS os dev sig
                               OPTIONAL_COMPONENTS cv)
find_package(OpenCV 4.0 REQUIRED COMPONENTS core rgbd
                                 OPTIONAL_COMPONENTS viz)

# Create variables for standard installation directories.
include(GNUInstallDirs)

# Control where libraries and executables are placed during the build.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

### yarpKinFu ###

# Create executable target.
add_executable(yarpKinFu src/yarpKinFu.cpp
                         src/YarpKinFu.hpp
                         src/YarpKinFu.cpp)

# Register dependencies.
target_link_libraries(yarpKinFu ${YARP_LIBRARIES} ${OpenCV_LIBS})

# Set compiler features.
target_compile_features(yarpKinFu PRIVATE cxx_std_11)

# Install target.
install(TARGETS yarpKinFu
        DESTINATION ${CMAKE_INSTALL_BINDIR})

### yarpDepthToPc ###

if(YARP_cv_FOUND AND OPENCV_VIZ_FOUND)
    # Create executable target.
    add_executable(yarpDepthToPc src/yarpDepthToPc.cpp
                                 src/YarpDepthToPc.hpp
                                 src/YarpDepthToPc.cpp)

    # Register dependencies.
    target_link_libraries(yarpDepthToPc ${YARP_LIBRARIES} ${OpenCV_LIBS})

    # Set compiler features.
    target_compile_features(yarpDepthToPc PRIVATE cxx_std_11)

    # Install target.
    install(TARGETS yarpDepthToPc
            DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()

# Configure and create uninstall target.
include(AddUninstallTarget)
