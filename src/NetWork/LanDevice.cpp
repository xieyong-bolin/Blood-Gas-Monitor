/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	LanDevice.Cpp
 * File Path:
 * Author:		Richard Xie
 * Version:		1.0
 * Description:
 *
 * History:
 *  Date		Author			CR number	CR Title
 */

#include "LanDevice.hpp"


LanDevice::LanDevice()
{

}


LanDevice::~LanDevice()
{

}


bool LanDevice::connectToHost(void)
{

    return true;
}


void LanDevice::updateIpAddress(INT8 *ipaddress)
{


}


INT32 LanDevice::sendPackage(INT8 *ptr, INT32U dataLen)
{

    return 0;
}


INT32 LanDevice::receivePackage(INT8 *ptr, INT32U dataLen)
{

    return 0;
}


bool  LanDevice::networkDeviceSelfTest(void)
{


    return true;
}


bool  LanDevice::setHostIp()
{

    return true;
}