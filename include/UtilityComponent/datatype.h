/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	datatype.h
 * File Path:   
 * Author:		Richard Xie
 * Version:		1.0
 * Description: implement for all datatype.h
 *
 *
 * History:
 *  Date		    Author			CR number	        CR Title
 */

#ifndef DATATYPE_H_
#define DATATYPE_H_

typedef   unsigned char         INT8U;
typedef   char                  INT8;
typedef   unsigned short        INT16U;
typedef   short                 INT16;
typedef   unsigned int          INT32U;
typedef   int                   INT32;
typedef   unsigned long         INT64U;
typedef   long                  INT64;






constexpr INT32U INFINITE =	0xFFFFFFFF;




//micros for thread priority
constexpr INT32 TIMESYNC_PRIORITY =         90;
constexpr INT32 FRONTEND_MGR_PRIORITY =     50;
constexpr INT32 FULLDISC_COLLECT_PRIORITY = 49;
constexpr INT32 DEFAULT_THREAD_PRIORITY =   1;


#endif