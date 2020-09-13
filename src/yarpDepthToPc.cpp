// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include <yarp/os/Log.h>
#include <yarp/os/Network.h>
#include <yarp/os/ResourceFinder.h>

#include "YarpDepthToPc.hpp"

int main(int argc, char * argv[])
{
    yarp::os::ResourceFinder rf;
    rf.setVerbose(true);
    rf.setDefaultContext("yarpDepthToPc");
    rf.setDefaultConfigFile("yarpDepthToPc.ini");
    rf.configure(argc, argv);

    yarp::os::Network yarp;

    if (!yarp::os::Network::checkNetwork())
    {
        yError("YARP network not found.\n");
        return 1;
    }

    YarpDepthToPc mod;
    return mod.runModule(rf);
}
