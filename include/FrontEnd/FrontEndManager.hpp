/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	FrontEndManager.hpp
 * File Path:
 * Author:		Richard Xie
 * Version:		1.0
 * Description:
 *
 * History:
 *  Date		Author			CR number	CR Title
 */

#ifndef FRONTENDMANAGER_H_
#define FRONTENDMANAGER_H_

#include "datatype.h"
#include "WorkThread.hpp"
#include "IDeviceModule.hpp"
#include "COModule.hpp"
#include "ParameterModule.hpp"
#include <vector>
using namespace std;

class FrontEndManager : public WorkThread
{

private:
    FrontEndManager(/* args */);
public:

    ~FrontEndManager();

    INT32U run();
    bool addDevice(IDeviceModule *device);
    bool deleteDevice(ModuleFlag flag);
    static FrontEndManager* getInstance();
private:
    std::vector<IDeviceModule*> deviceList;
    /* data */
};

#endif