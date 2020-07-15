add_executable(yarpKinFu main.cpp
                         YarpKinFu.hpp
                         YarpKinFu.cpp)

target_link_libraries(yarpKinFu YARP::YARP_os
                                YARP::YARP_init
                                YARP::YARP_dev
                                YARP::YARP_sig
                                opencv_rgbd)

target_compile_features(yarpKinFu PRIVATE cxx_std_11)

install(TARGETS yarpKinFu
        DESTINATION ${CMAKE_INSTALL_BINDIR})
