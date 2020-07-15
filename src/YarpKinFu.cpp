// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "YarpKinFu.hpp"

#include <yarp/os/LogStream.h>
#include <yarp/os/Property.h>
#include <yarp/os/Value.h>

bool YarpKinFu::configure(yarp::os::ResourceFinder & rf)
{
    yDebug() << rf.toString();

    if (!rf.check("remote", "sensor port prefix"))
    {
        yError() << "Missing --remote option (sensor port prefix)";
        return false;
    }

    period = rf.check("period", yarp::os::Value(DEFAULT_PERIOD_MS * 0.001), "sensor acquisition period (s)").asFloat64();

    std::string local = rf.check("local", yarp::os::Value(DEFAULT_LOCAL_PREFIX), "local port prefix").asString();
    std::string remote = rf.find("remote").asString();

    yarp::os::Property sensorOptions {
        {"device", yarp::os::Value("RGBDSensorClient")},
        {"localImagePort", yarp::os::Value(local + "/rgbImage:i")},
        {"localDepthPort", yarp::os::Value(local + "/depthImage:i")},
        {"localRpcPort", yarp::os::Value(local + "/rpc:o")},
        {"remoteImagePort", yarp::os::Value(remote + "/rgbImage:o")},
        {"remoteDepthPort", yarp::os::Value(remote + "/depthImage:i")},
        {"remoteRpcPort", yarp::os::Value(remote + "/rpc:i")}};

    if (!sensorDevice.open(sensorOptions) || !sensorDevice.view(iRGBDSensor))
    {
        return false;
    }

    if (!pointCloudPort.open(local + "/pcl:o"))
    {
        return false;
    }

    pointCloudPortWriter.attach(pointCloudPort);
    return true;
}

bool YarpKinFu::close()
{
    pointCloudPort.interrupt();
    pointCloudPort.close();
    sensorDevice.close();
    return true;
}

bool YarpKinFu::updateModule()
{
    return true;
}
