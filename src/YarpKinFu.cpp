// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "YarpKinFu.hpp"

#include <yarp/os/LogStream.h>
#include <yarp/os/Property.h>
#include <yarp/os/Value.h>

#include <yarp/sig/PointCloudUtils.h>

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
        {"remoteDepthPort", yarp::os::Value(remote + "/depthImage:o")},
        {"remoteRpcPort", yarp::os::Value(remote + "/rpc:i")}};

    if (!sensorDevice.open(sensorOptions) || !sensorDevice.view(iRGBDSensor))
    {
        yError() << "Unable to connect to remote camera.";
        return false;
    }

    if (!iRGBDSensor->getDepthIntrinsicParam(depthParams))
    {
        yError() << "Unable to retrieve depth intrinsic parameters.";
        return false;
    }

    depthWindow = new cv::viz::Viz3d("Yarp KinFu (depth)");

    return true;
}

bool YarpKinFu::close()
{
    delete depthWindow;
    depthWindow = nullptr;

    return sensorDevice.close();
}

bool YarpKinFu::updateModule()
{
    yarp::sig::FlexImage colorFrame;
    yarp::sig::ImageOf<yarp::sig::PixelFloat> depthFrame;

    if (!iRGBDSensor->getImages(colorFrame, depthFrame))
    {
       yWarning() << "Frame lost!";
       return true;
    }

    //yarp::sig::utils::depthRgbToPC(depthFrame, colorFrame, intrinsic);

    auto pc = yarp::sig::utils::depthToPC(depthFrame, depthParams);

    //cv::viz::WCube cube(cv::Vec3d::all(0), cv::Vec3d(1.0, 1.0, 1.0));
    //depthWindow->showWidget("cube", cube);

    cv::Mat points(pc.size(), 1, CV_32FC1, (void*)pc.getRawData());
    cv::viz::WCloud cloud(points);
    depthWindow->showWidget("cloud", cloud);

    depthWindow->spinOnce(1, true);
    //depthWindow->spin();
    return true;
}
