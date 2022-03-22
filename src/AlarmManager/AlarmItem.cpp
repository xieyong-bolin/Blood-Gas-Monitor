/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	AlarmItem.cpp
 * File Path:
 * Author:		Richard Xie
 * Version:		1.0
 * Description:
 *
 * History:
 *  Date		Author			CR number	CR Title
 */

#include "../../include/AlarmManager/AlarmItem.hpp"

AlarmItem::AlarmItem()
{
    alarm.clear();
    alarmPriority = AlarmPriority::unknowPriority;
    deleted = false;
    silenced = false;
    acknowledged = false;
}

AlarmItem::AlarmItem(ALARM alarmTemp) : alarm(alarmTemp)
{
    alarmPriority = alarmTemp.priority;
    deleted = false;
    silenced = false;
    acknowledged = false;
}

AlarmItem::~AlarmItem() {}

short AlarmItem::getChannel() const { return alarm.channel; }

AlarmId AlarmItem::getAlarmId() const { return alarm.id; }

AlarmData AlarmItem::getAlarmValue() const { return alarm.value; }

AlarmPriority AlarmItem::getPriority() const { return alarmPriority; }

size_t AlarmItem::getAlarmStrId() const { return 0; }

ALARM AlarmItem::getAlarm() const { return alarm; }

bool AlarmItem::isLatched() const {}

bool AlarmItem::getStatus() const { return deleted; }

void AlarmItem::setStatus(bool deletedFlag) { deleted = deletedFlag; }

INT32U AlarmItem::getTickCount() const { return alarm.tickcout; }

bool AlarmItem::isPhysical() const { return true; }

bool AlarmItem::isSilenced() const { return silenced; }

void AlarmItem::setSilenced(bool silencedFlag) { silenced = silencedFlag; }

bool AlarmItem::canDisable() const { return true; }

void AlarmItem::setAcknowledged(bool ack) { acknowledged = ack; }

bool AlarmItem::isAcknowledged() const { return acknowledged; }
