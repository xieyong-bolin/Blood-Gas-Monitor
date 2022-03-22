/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	IDeviceModule.hpp
 * File Path:
 * Author:		Richard Xie
 * Version:		1.0
 * Description:
 *
 * History:
 *  Date		Author			CR number	CR Title
 */

#ifndef IDEVICEMODULE_H__
#define IDEVICEMODULE_H__

#include "datatype.h"

using namespace std;

enum class ModuleFlag
{
    Parameter = 0,
    CO,
    PICCO
};


class IDeviceModule
{
private:
    /* data */
public:
    IDeviceModule(/* args */) {}
    IDeviceModule(ModuleFlag f) { flag = f; }
    virtual ~IDeviceModule() {}

    virtual INT8 shakeHand() = 0;     // connect to main board
    virtual INT8 initModule() = 0;    //
    virtual INT8 sendMessage() = 0;
    virtual INT8 receiveMesaage() = 0;
    virtual INT8 selftest() = 0;
    virtual INT8 process() = 0;

    ModuleFlag getFlag() { return flag; }
    void setFlag(ModuleFlag f) { flag = f; }

private:
    ModuleFlag flag;
};

#endif