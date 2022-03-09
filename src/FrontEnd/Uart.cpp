/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	Uart.cpp
 * File Path:
 * Author:		Richard Xie
 * Version:		1.0
 * Description:
 *
 * History:
 *  Date		Author			CR number	CR Title
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <getopt.h>
#include <termios.h>
#include "TTYProxy.h"
#include "Uart.h"


Uart::Uart()
{
	uartFd=0;

	pthread_mutexattr_t mattr;
	pthread_mutexattr_init(&mattr);
	pthread_mutexattr_setrobust_np(&mattr, PTHREAD_MUTEX_ROBUST_NP);
	pthread_mutexattr_settype(&mattr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&mutexLock, &mattr);
	pthread_mutexattr_destroy(&mattr);
}

Uart::~Uart()
{
	pthread_mutex_destroy(&mutexLock);
}



#ifndef CROSS_COMPILE
int Uart::initialize(const INT8 *uartDevice, INT32 speed, INT32 bits, INT8 event, INT32 stop)
{
	struct termios uartOpt;

	uartFd = tty_proxy_open(uartDevice, O_RDWR|O_NONBLOCK);
	tty_proxy_tcgetattr(uartFd ,&uartOpt);

	uartOpt.c_iflag &= ~(BRKINT|ICRNL|ISTRIP|IXON);
	uartOpt.c_oflag = 0;
	uartOpt.c_cflag &= ~(CSIZE|PARENB);
	uartOpt.c_cflag |= CS8 | (CLOCAL|CREAD); 
	uartOpt.c_lflag &= ~(ECHO|ICANON|IEXTEN|ISIG);
	uartOpt.c_iflag |= IGNBRK;
	uartOpt.c_cc [VMIN] = 0;
	uartOpt.c_cc [VTIME] = 0;

	//set com baud rate
	switch(speed)
	{
		case 2400:
			cfsetispeed(&uartOpt,B2400);
			cfsetospeed(&uartOpt,B2400);
			break;
		case 4800:
			cfsetispeed(&uartOpt,B4800);
			cfsetospeed(&uartOpt,B4800);
			break;
		case 9600:
			cfsetispeed(&uartOpt,B9600);
			cfsetospeed(&uartOpt,B9600);
			break;
		case 115200:
			cfsetispeed(&uartOpt,B115200);
			cfsetospeed(&uartOpt,B115200);
			break;
		case 460800:
		default:
			cfsetispeed(&uartOpt,B460800);
			cfsetospeed(&uartOpt,B460800);
			break;
	}

	if(tty_proxy_tcsetattr(uartFd,TCSANOW,&uartOpt))
	{
		uartFd=-1;
		printf("[STAR PRINT] Open COM  fail\n");
        return 1;
	}
	else
	{
		printf("[STAR PRINT] Open com sucess. handle = %d\n",uartFd);
	}

	tty_proxy_tcflush(uartFd, TCIFLUSH);

	return 0;
}
#else
INT32 Uart::initialize(const INT8 *uartDevice, INT32 speed, INT32 bits, INT8 event, INT32 stop)
{
	struct termios uartOpt;

	if(NULL == uartDevice)
	{
		printf("CUart::initialize: the point of uart name is NULL\n");
		return 1;
	}
	
	uartFd = open(uartDevice, O_RDWR|O_NONBLOCK);
	if(uartFd < 0)
	{
		printf("CUart::initialize: Open arm-uart fail\n");
		return 2;
	}

	if(0 != tcgetattr(uartFd ,&uartOpt))
	{
		printf("tcgetattr run fail\n");
        close(uartFd);
		return 2;
	}


	uartOpt.c_iflag &= ~(BRKINT|ICRNL|ISTRIP|IXON);
	uartOpt.c_oflag = 0;
	uartOpt.c_cflag &= ~(CSIZE|PARENB);
	uartOpt.c_cflag |= CS8 | (CLOCAL|CREAD); 
	uartOpt.c_lflag &= ~(ECHO|ICANON|IEXTEN|ISIG);
	uartOpt.c_iflag |= IGNBRK;
	uartOpt.c_cc [VMIN] = 0;
	uartOpt.c_cc [VTIME] = 0;

	//set com baud rate
	switch(speed)
	{
		case 2400:
			cfsetispeed(&uartOpt,B2400);
			cfsetospeed(&uartOpt,B2400);
			break;
		case 4800:
			cfsetispeed(&uartOpt,B4800);
			cfsetospeed(&uartOpt,B4800);
			break;
		case 9600:
			cfsetispeed(&uartOpt,B9600);
			cfsetospeed(&uartOpt,B9600);
			break;
		case 115200:
			cfsetispeed(&uartOpt,B115200);
			cfsetospeed(&uartOpt,B115200);
			break;
		case 460800:
		default:
			cfsetispeed(&uartOpt,B460800);
			cfsetospeed(&uartOpt,B460800);

			break;
	}

	if(tcsetattr(uartFd,TCSANOW,&uartOpt))
	{
		uartFd=-1;
        close(uartFd);

		printf("[UART PRINT] Open COM  fail\n");
        return 1;
	}
	else
	{
		printf("[UART PRINT] Open com sucess. handle = %d\n",uartFd);
	}

	tcflush(uartFd, TCIFLUSH);

	
	return 0;
}
#endif

INT32 Uart::readData(INT8U *data,INT64 dataLength)
{
	INT32 readBytes(0);
	pthread_mutex_lock(&mutexLock);
	if(!data || uartFd < 0)
	{
//		printf("CUart::read_data: the p_data point is null\n");
		pthread_mutex_unlock(&mutexLock);
		return -1;
	}
	
	readBytes =  read(uartFd, static_cast<void*>(data), dataLength);

	pthread_mutex_unlock(&mutexLock);

	return readBytes;
}


INT32 Uart::writeData(INT8U *data, INT64 dataLength)
{
	INT32 writeBytes(0);

	pthread_mutex_lock(&mutexLock);
	if(!data || uartFd < 0)
	{
//		printf("CUart::write_data: the p_data point is null\n");
		pthread_mutex_unlock(&mutexLock);
		return -1;
	}	

    writeBytes = write(uartFd, (void*)data, dataLength);

	pthread_mutex_unlock(&mutexLock);

	return writeBytes ;
}

bool Uart::terminate(void)
{
	bool retval(false);

	if(uartFd < 0)
		return retval;

	pthread_mutex_lock(&mutexLock);
	if(close(uartFd)==0)
	{
		printf("[UART PRINT] Close com sucess. handle = %d\n",uartFd);
		uartFd = -1;
		retval = true;
	}
	else
	{
		fprintf (stderr, "Close UART uart_fd_ =%d failed! \n", uartFd);
	}
	pthread_mutex_unlock(&mutexLock);

	return retval;
}


int Uart::getFd()
{
	return uartFd;
}



bool Uart::writeData()
{

}


bool Uart::readData()
{

}