/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	FrontEndManager.cpp
 * File Path:
 * Author:		Richard Xie
 * Version:		1.0
 * Description:
 *
 * History:
 *  Date		Author			CR number	CR Title
 */
#include <unistd.h>
#include "FrontEndManager.hpp"
using namespace std;

FrontEndManager::FrontEndManager(/* args */): WorkThread("FrontEndManager")
{
}

FrontEndManager::~FrontEndManager()
{
}


INT32U FrontEndManager::run()
{
    while (1)
    {
        if(isStopping())
            break;

        if(isSuspend())
        {
            usleep(100000);	// unit in microsecond.
            continue;
        }

        std::vector<IDeviceModule*>::reverse_iterator iter;

        for (iter = deviceList.rbegin(); iter != deviceList.rend(); iter++)
        {
            /* code */
            (*iter)->process();
        }
    }
}


bool FrontEndManager::addDevice(IDeviceModule *device)
{
    deviceList.push_back(device);
}


bool FrontEndManager::deleteDevice(ModuleFlag flag)
{
    INT8U i(0);
    std::vector<IDeviceModule*>::reverse_iterator iter;

    for (iter = deviceList.rbegin(); iter != deviceList.rend(); iter++, i++)
    {
        /* code */
        if(flag == (*iter)->getFlag())
        {
            //deviceList.erase(static_cast<int>(i));
            break;
        }
    }
}


FrontEndManager* FrontEndManager::getInstance()
{
    static FrontEndManager *ptr = nullptr;

    if (ptr == nullptr)
    {
        /* code */
        ptr = new FrontEndManager;
    }

    return ptr;
}