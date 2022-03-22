/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	IMessageProtoco.hpp
 * File Path:
 * Author:		Richard Xie
 * Version:		1.0
 * Description:
 *
 * History:
 *  Date		Author			CR number	CR Title
 */

#ifndef IMESSAGEPROTOCO_H__
#define IMESSAGEPROTOCO_H__

#include "IEncryptProtoco.hpp"

class IMessageProtoco
{
private:
    /* data */
public:
    IMessageProtoco(/* args */) {}
    virtual ~IMessageProtoco() {}

    virtual void packMessage()  = 0;
    virtual void parseMessage() = 0;

private:
    IEncryptProtoco* encryptProtoco;
};

#endif