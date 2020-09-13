// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __YARP_DEPTH_TO_PC__
#define __YARP_DEPTH_TO_PC__

#include <yarp/os/RFModule.h>
#include <yarp/dev/PolyDriver.h>
#include <yarp/dev/IRGBDSensor.h>
#include <yarp/sig/IntrinsicParams.h>

#define DEFAULT_LOCAL_PREFIX "/yarpDepthToPc"
#define DEFAULT_PERIOD_MS 20

class YarpDepthToPc : public yarp::os::RFModule
{
public:
    YarpDepthToPc()
        : iRGBDSensor(nullptr),
          period(DEFAULT_PERIOD_MS * 0.001)
    { }

    ~YarpDepthToPc()
    { close(); }

    virtual bool configure(yarp::os::ResourceFinder & rf) override;

    virtual double getPeriod() override
    { return period; }

    virtual bool updateModule() override;

    virtual bool close() override;

private:
    yarp::dev::PolyDriver sensorDevice;
    yarp::dev::IRGBDSensor * iRGBDSensor;
    yarp::sig::IntrinsicParams params;
    double period;
};

#endif // __YARP_DEPTH_TO_PC__
