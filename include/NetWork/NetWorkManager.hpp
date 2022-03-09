/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	NetWorkManager.hpp
 * File Path:
 * Author:		Richard Xie
 * Version:		1.0
 * Description:
 *
 * History:
 *  Date		Author			CR number	CR Title
 */

#ifndef NETWORKMANAGER_H__
#define NETWORKMANAGER_H__


#include "WorkThread.hpp"
#include "INetworkDevice.hpp"
#include "IMessageProtoco.hpp"
#include <vector>

using namespace std;


enum class ConnectionStatus
{
    connectUnkown = 0,   //once detect network device doesn't work, set connection flag to connectUnkown
    connection,
    disconnection
};


enum class ConnectionDevice
{
    deviceUnkown = 0,
    Lan,
    Wlan
};

enum class MessageProtocol
{
    unkown = 0,
    centralMonitorSystem,
    HIS,
    EMR
};


class NetWorkManager : public WorkThread
{

private:
    NetWorkManager();
    NetWorkManager(ConnectionDevice device, MessageProtocol pro);
public:

    virtual ~NetWorkManager();
    static NetWorkManager* getInstance();
    ConnectionStatus    isConnection(void);
    ConnectionDevice    getConnectedDevice(void);
    INT8 switchNetworkDevice(ConnectionDevice device);
    void switchProtocol(MessageProtocol pro);
protected:
	//implement this method
    INT32U run();

private:
    ConnectionDevice    connectedDevice;
    INetworkDevice*     networkDevice;   

    IMessageProtoco*    messageProtoco;
    MessageProtocol     protocol;

    ConnectionStatus    connectStatus;

    std::vector<INT8>     sendData;
    std::vector<INT8>     receiveData;
};


#endif