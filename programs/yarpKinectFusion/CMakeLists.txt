add_executable(yarpKinectFusion main.cpp
                                YarpKinectFusion.hpp
                                YarpKinectFusion.cpp)

target_link_libraries(yarpKinectFusion YARP::YARP_OS
                                       YARP::YARP_init
                                       YARP::YARP_dev
                                       YARP::YARP_sig)

target_compile_features(yarpKinectFusion PRIVATE cxx_std_11)

install(TARGETS yarpKinectFusion
        DESTINATION ${CMAKE_INSTALL_BINDIR})
