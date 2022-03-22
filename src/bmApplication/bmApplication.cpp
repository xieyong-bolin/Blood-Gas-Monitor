/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	bmApplication.cpp
 * File Path:
 * Author:		Richard Xie
 * Version:		1.0
 * Description: application program entry
 *
 *
 * History:
 *  Date		    Author			CR number	        CR Title
 */

#include "AlarmManager.hpp"
#include "FrontEndManager.hpp"
#include "MainScreen.hpp"
#include "MessageDistributor.hpp"
#include "NetWorkManager.hpp"
#include "OperationInstance.hpp"
#include "SettingManager.hpp"
#include "datatype.h"
#include "logging.hpp"

using namespace BMUsrInterface;

INT8 startThread()
{
    // start alarm thread
    AlarmManager::getInstance()->start();
    NetWorkManager::getInstance()->start();

    return 0;
}


INT8 loadConfiguration()
{
    SettingManager::getInstance()->loadSettingData();
    return 0;
}


INT8 loadFrontEnd()
{
    for (INT8U i = 0; i < static_cast<INT8U>(FrontEndConfigurtion::num); i++)
    {
        IDeviceModule *ptr = nullptr;

        if (SettingManager::getInstance()->frontEndConfigMask(FrontEndConfigurtion::COModule))
        {
            ptr = new COModule;
            FrontEndManager::getInstance()->addDevice(ptr);
        }
        else if (SettingManager::getInstance()->frontEndConfigMask(FrontEndConfigurtion::Param6))
        {
            ptr = new ParameterModule;
            FrontEndManager::getInstance()->addDevice(ptr);
        }
        else if (SettingManager::getInstance()->frontEndConfigMask(FrontEndConfigurtion::PICCO))
        {
        }
        else if (SettingManager::getInstance()->frontEndConfigMask(FrontEndConfigurtion::AG))
        {
        }
    }

    FrontEndManager::getInstance()->start();
}


INT32 main(INT32 argc, INT8 const *argv[])
{
    /* code */
    // load configuration
    loadConfiguration();

    // load clinical data
    OperationInstance::getInstance()->loadData();
    OperationInstance::getInstance()->start();

    // start thread
    startThread();

    loadFrontEnd();


    return 0;
}
