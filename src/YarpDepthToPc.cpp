// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "YarpDepthToPc.hpp"

#include <yarp/os/LogStream.h>

bool YarpDepthToPc::configure(yarp::os::ResourceFinder & rf)
{
    yDebug() << rf.toString();
    return true;
}

bool YarpDepthToPc::close()
{
    return true;
}

bool YarpDepthToPc::updateModule()
{
    return true;
}
