/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	NetWorkManager.cpp
 * File Path:
 * Author:		Richard Xie
 * Version:		1.0
 * Description:
 *
 * History:
 *  Date		Author			CR number	CR Title
 */

#include <array>
#include <unistd.h>

#include "NetWorkManager.hpp"
#include "LanDevice.hpp"
#include "WLanDevice.hpp"
#include "CentralMonitorSystemProtocol.hpp"

using namespace std;


NetWorkManager::NetWorkManager()
:WorkThread("NetWorkManager")
{
    networkDevice = nullptr;
    messageProtoco = nullptr;
    connectStatus = ConnectionStatus::connectUnkown;
    protocol = MessageProtocol::unkown;
}


NetWorkManager::NetWorkManager(ConnectionDevice device, MessageProtocol pro)
:WorkThread("NetWorkManager")
{
    if(device == ConnectionDevice::Lan)
        networkDevice = new LanDevice;
    else if(device == ConnectionDevice::Wlan)
        networkDevice = new WLanDevice;
    else
        networkDevice = nullptr;

    protocol = pro;

    if (protocol == MessageProtocol::centralMonitorSystem )
    {
        messageProtoco = new CentralMonitorSystemProtocol;
    }
    else
        messageProtoco = nullptr;

    connectStatus = ConnectionStatus::connectUnkown;
    
}

NetWorkManager::~NetWorkManager()
{

}


INT32U NetWorkManager::run()
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

        switch (isConnection())
        {
            case ConnectionStatus::connectUnkown:
                /* code */
                if (networkDevice == nullptr)
                {
                    /* code */
                    return 1;
                }

                if(!networkDevice->networkDeviceSelfTest())
                {
                    //should register an alarm to identify network device is unavailable
                }
                else
                {
                    connectStatus = ConnectionStatus::disconnection;  //device is okay, ready to connect
                }
                break;

            case ConnectionStatus::disconnection:
                if(networkDevice != nullptr)
                    networkDevice->connectToHost();
                break;

            case ConnectionStatus::connection:
                if(networkDevice != nullptr && messageProtoco != nullptr)
                {
                    //std::array<INT8, 1024> temp ={0};
                    INT8 array[1024] = {0};

                    messageProtoco->packMessage();
                    networkDevice->sendPackage(array, 1024);
                }

                if(networkDevice != nullptr && messageProtoco != nullptr)
                {
                    //std::array<INT8, 1024> temp ={0};
                    INT8 array[1024] = {0};

                    networkDevice->receivePackage(array, 1024);
                    messageProtoco->parseMessage();

                }
                break;

            default:
                break;
        }
    }
    

    return 0;
}


ConnectionStatus NetWorkManager::isConnection(void)
{
    return connectStatus;
}


ConnectionDevice NetWorkManager::getConnectedDevice(void)
{
    return connectedDevice;
}


NetWorkManager* NetWorkManager::getInstance()
{
    static NetWorkManager *instance = nullptr;

    if(nullptr == instance)
    {
        instance = new NetWorkManager;
    }

    return instance;
}


INT8 NetWorkManager::switchNetworkDevice(ConnectionDevice device)
{
    if(connectedDevice == device)
        return -1;

    connectedDevice = device;  // configure which network device should use next
    if (ConnectionDevice::Lan == connectedDevice)
    {
        /* code */
        delete networkDevice;
        networkDevice = nullptr;
        networkDevice = new LanDevice;
    }
    else if (ConnectionDevice::Wlan == connectedDevice)
    {
        delete networkDevice;
        networkDevice = nullptr;
        networkDevice = new WLanDevice;
    }

    connectStatus = ConnectionStatus::disconnection;   //after change used network device, the connected status should set to disconnetion

    return 0;
}



void NetWorkManager::switchProtocol(MessageProtocol pro)
{
     protocol = pro;
    if (protocol == MessageProtocol::centralMonitorSystem)
    {
        delete messageProtoco;
        messageProtoco = new CentralMonitorSystemProtocol;
        /* code */
    }
    else if(protocol == MessageProtocol::HIS)
    {

    }
    else if(protocol == MessageProtocol::EMR)
    {

    }
    
}