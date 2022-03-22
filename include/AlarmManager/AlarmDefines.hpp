/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	AlarmDefines.hpp
 * File Path:
 * Author:		Richard Xie
 * Version:		1.0
 * Description:
 *
 * History:
 *  Date		Author			CR number	CR Title
 */

#ifndef ALARM_DEFS_H_
#define ALARM_DEFS_H_

#include "../UtilityComponent/datatype.h"
#include <time.h>


enum class AlarmPriority
{
    unknowPriority = -1,
    lowPriority,
    middlePriority,
    highPriority
};


enum class AlarmType
{
    physiological = 0,
	technical,
	other
};


enum class AlarmId
{
    unkownId,
    PHHigh,
    PHLow,
    So2High,
    So2Low,
    SPCO2High,
    SPCO2Low,
    tempHigh,
    tempLow,
	batteryLow,
	batteryVeryLow,
    alarmNum
};


using AlarmMap = struct ALARMMAP
{
    AlarmId id;
    AlarmType type;
    AlarmPriority priority;
};


union AlarmData
{
	int value;

	struct stubBP
	{
		int sys 	: 10;
		int dia 	: 10;
		int mean 	: 10;
		int noused	: 2;
	}valueBP;

	struct stubST
	{
		unsigned int lead1	: 4;
		int value1			: 12;
		unsigned int lead2	: 4;
		int value2			: 12;
	}valueST;
};


enum class AlarmMode
{
	AlarmModeNormal  = 0,	// Play alarm sound
	AlarmModeSilence,	// Silence alarm sound for ALARM RESET.
	AlarmModePause,		// Pause alarm sound
	AlarmModeStop		// Stop alarm sound
};


using ALARM = struct tagAlarm
{
	AlarmId 	id;
    AlarmPriority priority;
	time_t		time;
	INT64U     group_id;
	size_t		tickcout;
	AlarmData	value;
	INT16		channel;
	bool		demo;

	void clear()
	{
		id 			= AlarmId::unkownId;
        priority    = AlarmPriority::unknowPriority;
		time 		= 0;
		group_id    = -1;
		tickcout    = 0;
		value.value = 0;
		channel 	= 0;
		demo	    = false;
	}
};


enum class AlarmAction
{
	AlarmAdd,
	AlarmDel,
	AlarmUpdate
};


typedef struct tagAlarmElem
{
	ALARM 			alarm;
	AlarmAction 	action;
}AlarmElem;

#endif