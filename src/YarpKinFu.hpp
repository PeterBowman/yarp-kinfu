// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __YARP_KINFU__
#define __YARP_KINFU__

#include <yarp/os/Property.h>
#include <yarp/os/RFModule.h>
#include <yarp/dev/IRGBDSensor.h>
#include <yarp/dev/PolyDriver.h>
#include <yarp/sig/PointCloud.h>

#include <opencv2/viz.hpp>

#define DEFAULT_LOCAL_PREFIX "/yarpKinFu"
#define DEFAULT_PERIOD_MS 20

class YarpKinFu : public yarp::os::RFModule
{
public:
    YarpKinFu() : iRGBDSensor(nullptr),
                  depthWindow(nullptr),
                  period(DEFAULT_PERIOD_MS * 0.001)
    { }

    ~YarpKinFu()
    { close(); }

    virtual bool configure(yarp::os::ResourceFinder & rf) override;

    virtual double getPeriod() override
    { return period; }

    virtual bool updateModule() override;

    virtual bool close() override;

private:
    yarp::dev::PolyDriver sensorDevice;
    yarp::dev::IRGBDSensor * iRGBDSensor;
    yarp::os::Property depthParams;
    cv::viz::Viz3d * depthWindow;
    double period;
};

#endif // __YARP_KINFU__
