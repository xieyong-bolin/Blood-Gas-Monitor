/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	Uart.hpp
 * File Path:
 * Author:		Richard Xie
 * Version:		1.0
 * Description:
 *
 * History:
 *  Date		Author			CR number	CR Title
 */

#ifndef UART_H_
#define UART_H_

#include <pthread.h>
#include "datatype.h"
using namespace std;

class Uart
{
public:
	Uart();
	virtual ~Uart();

	INT32 initialize(const INT8 *uartDevice, INT32 speed, INT32 bits, INT8 event, INT32 stop);
	bool terminate(void);

	INT32 getFd()  __attribute__((no_instrument_function));
	bool readData(void);
	bool writeData(void);

private:
	INT32 readData(INT8U *data, INT64 dataLength)  __attribute__((no_instrument_function));
	INT32 writeData(INT8U *data, INT64 dataLength);
private:
	pthread_mutex_t	 mutexLock;
	INT32 buff[1024];
	INT32 uartFd;
};


#endif

