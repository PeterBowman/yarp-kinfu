// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include <yarp/os/Log.h>
#include <yarp/os/Network.h>
#include <yarp/os/ResourceFinder.h>

#include "YarpKinectFusion.hpp"

int main(int argc, char * argv[])
{
    yarp::os::ResourceFinder rf;
    rf.setVerbose(true);
    rf.setDefaultContext("yarpKinectFusion");
    rf.setDefaultConfigFile("yarpKinectFusion.ini");
    rf.configure(argc, argv);

    yarp::os::Network yarp;

    if (!yarp::os::Network::checkNetwork())
    {
        yError("YARP network not found.\n");
        return 1;
    }

    YarpKinectFusion mod;
    return mod.runModule(rf);
}
