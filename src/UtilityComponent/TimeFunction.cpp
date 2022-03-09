/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	TimeFunction.Cpp
 * File Path:
 * Author:		Richard Xie
 * Version:		1.0
 * Description:
 *
 * History:
 *  Date		Author			CR number	CR Title
 */


#include <stdlib.h>
#include <sys/select.h>
#include <sys/time.h>
#include <time.h>
#include <libintl.h>
#include <memory.h>
#include <unistd.h>

#include "../../include/AlarmManager/AlarmManager.hpp"
#include "../../include/UtilityComponent/TimeFunction.hpp"

extern INT32	g_pop_up_code;

INT32U getTickCount()
{
	timespec ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	INT32U millsecs = ts.tv_sec*1000 + ts.tv_nsec/1000000;
	return millsecs;
}

INT64U getTickCountUs()
{
	timespec ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	INT64U nanosecs = ts.tv_sec*1000000 + ts.tv_nsec/1000;

	return nanosecs;
}

INT32 safeSleep(INT64 msTimeOut)
{
	timeval tv;

	long seconds = msTimeOut / 1000;
	long useconds = (msTimeOut - seconds*1000)*1000;
	tv.tv_sec = seconds;
	tv.tv_usec = useconds;

	return select(1, NULL, NULL, NULL, &tv);
}

bool getTimeSpec(struct timespec *ts, INT64 msTimeOut)
{
	struct timeval tv;

    if ( -1 == gettimeofday(&tv, NULL))
    	return false;

    TIMEVAL_TO_TIMESPEC(&tv, ts);
	ts->tv_nsec += msTimeOut * 1000000;
	if (ts->tv_nsec >= 1000000000)
	{
		ts->tv_sec += ts->tv_nsec / 1000000000;
		ts->tv_nsec %= 1000000000;
	}

    return true;
}


tm* getLocalTime(struct tm& retTime)
{
	time_t aTime = time(NULL);

	return localtime_r(&aTime, &retTime);
}

tm* getLocalTime(time_t &aTime, struct tm& retTime)
{
	return localtime_r(&aTime, &retTime);
}

void setLocaleInfo(const char* charSet)
{
	bool setSuccess(false);

	char territory[100];
	char codeSet[100];
	char directory[256];

	memset(territory,0,sizeof(territory));
	memset(codeSet,0,sizeof(codeSet));
	sscanf(charSet, "%[^'.'].%[^'.']", territory, codeSet);
#ifdef __arm__
	snprintf(directory, sizeof(directory), "/Target/local/BM/%s/LC_MESSAGES/BM.mo", territory);
#else
	snprintf(directory, sizeof(directory), "/usr/share/locale/%s/LC_MESSAGES/BM.mo", territory);
#endif
	INT32 accessRet = access(directory, F_OK);
	if( accessRet == 0 )
	{
		if( setlocale( LC_MESSAGES, charSet ) != NULL )
		{
			setSuccess = true;
		}
#ifdef __arm__
		bindtextdomain("BM", "/Target/local/BM/");
#endif
		textdomain("BM");
	}
	printf("LANGUAGE(%d)(%s):%s\n", accessRet, setlocale( LC_MESSAGES, NULL ), directory);

	if( setSuccess == false )
	{
#ifdef CROSS_COMPILE
		ALARMMGR_PTR->register_system_error_alarm(LOAD_RESOURCE_FAILED, LOAD_RESOURCE_FAIL, false);
		g_pop_up_code |= POPUP_SYS_ERR_RESOURCE;
#endif
	}
}

bool setZoneInfo(const char* tz)
{
	if ( !tz || !strcmp(tz,"") )
	{
		printf("set time zone error: time zone is null.\n");
		return false;
	}

	int ret = setenv("TZ", tz, 1);
	tzset();

	printf("TIMEZONE: Set time zone(%d): %s \n",ret, tz);
	return true;
}

INT32 getDaysOfMonth(int year,int month)// days
{
	switch(month)
	{
		case 1:return 31;break;
		case 2:return 28+getLeap(year);break;
		case 3:return 31;break;
		case 4:return 30;break;
		case 5:return 31;break;
		case 6:return 30;break;
		case 7:return 31;break;
		case 8:return 31;break;
		case 9:return 30;break;
		case 10:return 31;break;
		case 11:return 30;break;
		case 12:return 31;break;
	}

	return 31;
}

INT32 getLeap(int year)
{
	if(year <= 0)
		return 1;
	if(year%4==0)
	{
		if(year%100==0)
		{
			if(year%400==0)
				return 1;
			else
				return 0;
		}
		else
			return 1;
	}
	else
		return 0;
}

time_t myTimegm(struct tm *tm)
{
    time_t t;
    char *tz;

    tz = getenv("TZ");
    setenv("TZ", "", 1);
    tzset();
    t = mktime(tm);
    if (tz)
        setenv("TZ", tz, 1);
    else
        unsetenv("TZ");
    tzset();
    return t;
}
