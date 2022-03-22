/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	AlarmManager.cpp
 * File Path:
 * Author:		Richard Xie
 * Version:		1.0
 * Description:
 *
 * History:
 *  Date		Author			CR number	CR Title
 */
#include <unistd.h>

#include "AlarmManager.hpp"


AlarmManager::AlarmManager() : WorkThread("AlarmManager") {}


AlarmManager::~AlarmManager() {}


INT32U AlarmManager::run()
{
    while (1)
    {
        if (isStopping())
            break;

        if (isSuspend())
        {
            usleep(100000);    // unit in microsecond.

            continue;
        }

        manageAlarm();
        usleep(100000);    // unit in microsecond.
    }
}


void AlarmManager::manageAlarm() {}


AlarmManager *AlarmManager::getInstance()
{
    static AlarmManager *instance = nullptr;

    if (nullptr == instance)
    {
        instance = new AlarmManager;
    }

    return instance;
}