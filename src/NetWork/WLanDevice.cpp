/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	WLanDevice.Cpp
 * File Path:
 * Author:		Richard Xie
 * Version:		1.0
 * Description:
 *
 * History:
 *  Date		Author			CR number	CR Title
 */

#include "WLanDevice.hpp"

WLanDevice::WLanDevice()
{

}


WLanDevice::~WLanDevice()
{
    
}


bool WLanDevice::connectToHost(void)
{

    return true;
}


void WLanDevice::updateIpAddress(INT8 *ipaddress)
{


}


INT32 WLanDevice::sendPackage(INT8 *ptr, INT32U dataLen)
{

    return 0;
}


INT32 WLanDevice::receivePackage(INT8 *ptr, INT32U dataLen)
{

    return 0;
}


bool  WLanDevice::networkDeviceSelfTest(void)
{


    return true;
}


bool  WLanDevice::setHostIp()
{

    return true;
}