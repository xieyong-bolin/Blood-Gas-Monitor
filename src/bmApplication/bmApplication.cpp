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

#include "datatype.h"
#include "logging.hpp"
#include "OperationInstance.hpp"
#include "MessageDistributor.hpp"
#include "AlarmManager.hpp"
#include "SettingManager.hpp"
#include "NetWorkManager.hpp"


INT8   startThread()
{
    //start alarm thread
    AlarmManager::getInstance()->start();
    NetWorkManager::getInstance()->start();
    return 0;
}



INT8   loadConfiguration()
{
    SettingManager::getInstance()->loadSettingData();
    return 0;
}


INT32  main(INT32 argc, INT8 const *argv[])
{

    /* code */
    //load configuration
    loadConfiguration();

    //load clinical data
    OperationInstance::getInstance()->loadData();
    OperationInstance::getInstance()->start();

    //start thread

    
    startThread();


    return 0;
}
