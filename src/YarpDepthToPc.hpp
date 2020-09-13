// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __YARP_DEPTH_TO_PC__
#define __YARP_DEPTH_TO_PC__

#include <yarp/os/RFModule.h>

class YarpDepthToPc : public yarp::os::RFModule
{
public:
    YarpDepthToPc()
    { }

    ~YarpDepthToPc()
    { close(); }

    virtual bool configure(yarp::os::ResourceFinder & rf) override;

    virtual double getPeriod() override
    { return 0.01; }

    virtual bool updateModule() override;

    virtual bool close() override;

private:
};

#endif // __YARP_DEPTH_TO_PC__
