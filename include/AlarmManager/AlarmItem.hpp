/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	AlarmItem.hpp
 * File Path:
 * Author:		Richard Xie
 * Version:		1.0
 * Description:
 *
 * History:
 *  Date		Author			CR number	CR Title
 */

#ifndef ALARMITEM_H_
#define ALARMITEM_H_

#include "datatype.h"
#include "AlarmDefines.hpp"
#include <stdint.h>

class AlarmItem
{
public:
	AlarmItem();
	AlarmItem(ALARM alarmTemp);
	virtual ~AlarmItem();

	time_t			getTimestamp()const {return alarm.time;};
	INT16 			getChannel() const;
	AlarmId 		getAlarmId() const;
	AlarmData		getAlarmValue() const;
	AlarmPriority	getPriority() const;
	size_t			getAlarmStrId() const;
	ALARM			getAlarm() const;
	bool			isLatched() const;
	bool 			getStatus() const;
	void 			setStatus(bool deletedFlag);
	INT32U			getTickCount() const;
	bool 			isPhysical() const;
	bool 			isSilenced() const;
	void 			setSilenced(bool silencedFlag);
	bool 			canDisable() const;
	void			setAcknowledged(bool ack);
	bool			isAcknowledged() const;
private:
	ALARM			alarm;
	AlarmPriority	alarmPriority;
	bool 			deleted;
	bool			silenced;
	bool			acknowledged;
};


#endif /* ALARMITEM_H_ */
