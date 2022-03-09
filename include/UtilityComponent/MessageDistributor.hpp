/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	MessageDistributor.hpp
 * File Path:   
 * Author:		Richard Xie
 * Version:		1.0
 * Description: MessageDistributor head file
 *
 *
 * History:
 *  Date		    Author			CR number	        CR Title
 */

#ifndef MESSAGEDISTRIBUTOR_H__
#define MESSAGEDISTRIBUTOR_H__

//#include <uv.h>
#include "datatype.h"

class MessageDistributor
{
private:
    /* data */
    MessageDistributor(/* args */);
public:
    
    ~MessageDistributor();
    MessageDistributor* getInstance();
    INT32 libInit();
    INT32 libuvRun();
    INT32 libConfigure();
    INT32 freeLoop();

private:
   // uv_loop_t           *loop;
};











#endif