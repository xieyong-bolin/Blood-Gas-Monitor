/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	UartThread.cpp
 * File Path:
 * Author:		Richard Xie
 * Version:		1.0
 * Description:
 *
 * History:
 *  Date		Author			CR number	CR Title
 */
#include <unistd.h>
#include "UartThread.hpp"
using namespace std;


UartThread::UartThread() : WorkThread("UartThread")
{
}


UartThread::~UartThread()
{
}


INT32U UartThread::run()
{
    while (1)
    {
        if(isStopping())
            break;

        if(isSuspend())
        {
            usleep(100000);	// unit in microsecond.
            continue;
        }

        std::vector<Uart>::reverse_iterator iter;

        for (iter = uartList.rbegin(); iter != uartList.rend(); iter++)
        {
            /* code */
            iter->readData();
        }
    }
    
    return 0;
}


void UartThread::addUart(Uart item)
{
   // item.initialize();
	uartList.push_back(item);
}


INT8 UartThread::registerUartDevice(Uart item)
{


    return 0;
}