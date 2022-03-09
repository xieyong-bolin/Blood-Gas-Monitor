/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	CentralMonitorSystemProtocol.hpp
 * File Path:
 * Author:		Richard Xie
 * Version:		1.0
 * Description:
 *
 * History:
 *  Date		Author			CR number	CR Title
 */


#ifndef CENTRALMONITORSYSTEMPROTOCOL_H_
#define CENTRALMONITORSYSTEMPROTOCOL_H_

#include "IMessageProtoco.hpp"

class CentralMonitorSystemProtocol : public IMessageProtoco
{
private:
    /* data */
public:
    CentralMonitorSystemProtocol(/* args */);
    ~CentralMonitorSystemProtocol();


    virtual void packMessage();
    virtual void parseMessage();
};




#endif