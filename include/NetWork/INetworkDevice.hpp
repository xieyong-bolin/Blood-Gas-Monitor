/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	INetworkDevice.hpp
 * File Path:
 * Author:		Richard Xie
 * Version:		1.0
 * Description:
 *
 * History:
 *  Date		Author			CR number	CR Title
 */

#ifndef INETWORKDEVICE_H__
#define INETWORKDEVICE_H__

#include "datatype.h"


class  INetworkDevice
{
private:
    /* data */
    INT8 ipAddress[8];
public:

    virtual bool connectToHost(void) = 0;
    virtual void updateIpAddress(INT8 *ipaddress) = 0;
    virtual INT32 sendPackage(INT8 *ptr, INT32U dataLen) = 0;
    virtual INT32 receivePackage(INT8 *ptr, INT32U dataLen) = 0;
    virtual bool   networkDeviceSelfTest() = 0;
    virtual bool setHostIp() = 0;
    //virtual INT32  
};



#endif