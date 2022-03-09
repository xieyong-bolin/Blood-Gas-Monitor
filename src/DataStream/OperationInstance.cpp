///////////////////////////////////////////////////////////
//  OperationInstance.cpp
//  Implementation of the Class OperationInstance
//  Created on:      28-Jan-2022 10:40:20 AM
//  Original author: Richard Xie
///////////////////////////////////////////////////////////

#include <unistd.h>
#include "OperationInstance.hpp"


OperationInstance::OperationInstance()
:WorkThread("OperationInstance")
{
    hct = new HCT;
    ph = new PH;
    kplus = new KPlus;
    so2 = new SO2;
    spco2 = new SPCO2;
    spo2 = new SPO2;
    temp = new Temp;
}



OperationInstance::~OperationInstance()
{
    delete hct;
    hct = nullptr;

    delete ph;
    ph = nullptr;

    delete kplus;
    kplus = nullptr;

    delete so2;
    so2 = nullptr;

    delete spco2;
    spco2 = nullptr;

    delete spo2;
    spo2 = nullptr;

    delete temp;
    temp = nullptr;
}

INT32U OperationInstance::run()
{

    while(1)
    {
        if(isStopping())
            break;

        if(isSuspend())
        {
            usleep(100000);	// unit in microsecond.

            continue;
        }
    }
}

bool OperationInstance::loadData()
{
    hct->loadData();
    ph->loadData();
    kplus->loadData();
    so2->loadData();
    spco2->loadData();
    spo2->loadData();
    temp->loadData();

    return true;
}


INT32 OperationInstance::saveData()
{
    hct->saveData();
    ph->saveData();
    kplus->saveData();
    so2->saveData();
    spco2->saveData();
    spo2->saveData();
    temp->saveData();

    return 0;
}


bool OperationInstance::clearData()
{
    hct->clearData();
    ph->clearData();
    kplus->clearData();
    so2->clearData();
    spco2->clearData();
    spo2->clearData();
    temp->clearData();

    return true;
}


OperationInstance* OperationInstance::getInstance()
{
    static OperationInstance *instancePtr = nullptr;

    if(nullptr == instancePtr)
    {
        instancePtr = new OperationInstance;
    }

    return instancePtr;
}