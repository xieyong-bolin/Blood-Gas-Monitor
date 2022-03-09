/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	TimeFunction.hpp
 * File Path:
 * Author:		Richard Xie
 * Version:		1.0
 * Description:
 *
 * History:
 *  Date		Author			CR number	CR Title
 */
#ifndef TIMEFUNCTION_H__
#define TIMEFUNCTION_H__

#include <time.h>
#include "datatype.h"


INT32U getTickCount() __attribute__((no_instrument_function));
INT64U getTickCountUs() __attribute__((no_instrument_function));
INT32  safeSleep(long msTimeOut);
bool getTimeSpec(struct timespec *ts, INT64 msTimeOut);
void setLocaleInfo(const char* charSet);
bool setZoneInfo(const char* tz);
tm* getLocalTime(struct tm& retTime);
tm* getLocalTime(time_t &aTime, struct tm& retTime);
INT32 getDaysOfMonth(INT32 year,INT32 month);
INT32 getLeap(INT32 year);

#endif 
