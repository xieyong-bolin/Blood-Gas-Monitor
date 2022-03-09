/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	MessageDistributor.cpp
 * File Path:   
 * Author:		Richard Xie
 * Version:		1.0
 * Description: MessageDistributor implementation
 *
 *
 * History:
 *  Date		    Author			CR number	        CR Title
 */

#include "MessageDistributor.hpp"
#include <cstdlib>
using namespace std;


MessageDistributor::MessageDistributor(/* args */)
{

    libInit();
}

MessageDistributor::~MessageDistributor()
{
    freeLoop();
}


MessageDistributor* MessageDistributor::getInstance()
{
    static MessageDistributor *instance = nullptr;
    
    if (instance == nullptr)
    {
        instance = new MessageDistributor;
    }
    
    return instance;
}


INT32 MessageDistributor::libInit()
{
   // loop = new uv_loop_t;
   // uv_loop_init(loop);
}



INT32 MessageDistributor::libuvRun()
{
  //  uv_run(loop, UV_RUN_DEFAULT);
}


INT32 MessageDistributor::libConfigure()
{

}


INT32 MessageDistributor::freeLoop()
{
 //    uv_loop_close(loop);
 //    free(loop);
}