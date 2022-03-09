/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	UartThread.hpp
 * File Path:
 * Author:		Richard Xie
 * Version:		1.0
 * Description:
 *
 * History:
 *  Date		Author			CR number	CR Title
 */

#ifndef UARTTHREAD_H_
#define UARTTHREAD_H_

#include "datatype.h"
#include "WorkThread.hpp"
#include "Uart.h"
#include <vector>

class UartThread: public WorkThread
{
public:
    UartThread(/* args */);
    ~UartThread();

    INT8 registerUartDevice(Uart item);
    INT32U run();
    void addUart(Uart item);
private:
    /* data */
    std::vector<Uart> uartList;
};


#endif