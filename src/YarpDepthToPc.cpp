// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "YarpDepthToPc.hpp"

#include <cstring>

#include <yarp/os/LogStream.h>
#include <yarp/os/Property.h>
#include <yarp/os/Value.h>

#include <yarp/sig/Image.h>
#include <yarp/sig/PointCloud.h>
#include <yarp/sig/PointCloudUtils.h>

#include <opencv2/viz/widgets.hpp>

bool YarpDepthToPc::configure(yarp::os::ResourceFinder & rf)
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
        return false;
    }

    yarp::os::Property intrinsic;

    if (!iRGBDSensor->getDepthIntrinsicParam(intrinsic))
    {
        yError() << "Unable to retrieve intrinsic parameters.";
        return false;
    }

    params.fromProperty(intrinsic);
    window.setViewerPose(cv::Affine3f::Identity());
    return true;
}

bool YarpDepthToPc::close()
{
    sensorDevice.close();
    return true;
}

bool YarpDepthToPc::updateModule()
{
    yarp::sig::ImageOf<yarp::sig::PixelFloat> depthFrame;

    if (!iRGBDSensor->getDepthImage(depthFrame))
    {
        return true;
    }

    yarp::sig::PointCloudXYZ pc = yarp::sig::utils::depthToPC(depthFrame, params);

    if (pc.size() == 0)
    {
        return true;
    }

    cv::Mat points(pc.size(), 1, CV_32FC3, const_cast<char *>(pc.getRawData()));

    cv::viz::WCloud cloudWidget(points, cv::viz::Color::white());
    window.showWidget("cloud", cloudWidget);
    window.spinOnce(1, true);

    return true;
}
