/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	LanDevice.hpp
 * File Path:
 * Author:		Richard Xie
 * Version:		1.0
 * Description:
 *
 * History:
 *  Date		Author			CR number	CR Title
 */


#ifndef LANDEVICE_H__
#define LANDEVICE_H__
using namespace std;
#include "INetworkDevice.hpp"

class LanDevice:public INetworkDevice
{

public:
    LanDevice();
    virtual ~LanDevice();

    virtual bool  connectToHost(void);
    virtual void  updateIpAddress(INT8 *ipaddress);
    virtual INT32 sendPackage(INT8 *ptr, INT32U dataLen);
    virtual INT32 receivePackage(INT8 *ptr, INT32U dataLen);
    virtual bool  networkDeviceSelfTest(void);
    virtual bool  setHostIp(); 
};


#endif