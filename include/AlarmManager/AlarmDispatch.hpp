/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	AlarmDispatch.hpp
 * File Path:
 * Author:		Richard Xie
 * Version:		1.0
 * Description:
 *
 * History:
 *  Date		Author			CR number	CR Title
 */

#ifndef ALARMDISPATCH_H_
#define ALARMDISPATCH_H_

#include <list>
#include <vector>
#include <map>
#include <pthread.h>
#include "AlarmItem.hpp"
#include "AutoLock.hpp"
#include "TimeFunction.hpp"

using namespace std;

typedef std::map< short, std::list<AlarmItem> >					ALARM_MAP;
typedef std::map< short, std::list<AlarmItem> >::iterator		ALARM_ITER;
typedef std::vector<std::pair<INT16, AlarmId> > 				MUTE_TECH_VEC;

class AlarmDispatch
{
public:
	AlarmDispatch();
	~AlarmDispatch();

	bool 	addAlarm( ALARM alarm );

	bool 	removeAlarm( INT16 channel, AlarmId id, bool forceDelete=false );
	void 	reset();

	bool 	isAlarmExist( INT16 channel, AlarmId id ) __attribute__((no_instrument_function));

	void 	getHighestAlarmPri( INT16& audioPri, INT16& msgPri, INT16& ledPri ) __attribute__((no_instrument_function));

	void 	getAlarms( INT16 channel, AlarmPriority priority, std::vector<AlarmItem>& alarms ) __attribute__((no_instrument_function));
	void 	getAlarms( AlarmPriority priority, std::vector<AlarmItem>& alarms ) __attribute__((no_instrument_function));
	void 	getAlarms( std::vector<AlarmItem>& alarms ) __attribute__((no_instrument_function));

	bool	getAlarmInfo( INT16 channel, AlarmId id, ALARM& alarm );
	void 	deleteObsolete() __attribute__((no_instrument_function));
	bool 	isChannelExisted(INT16 channel) __attribute__((no_instrument_function));
	void 	clearLatchedAlarm();

	void    clearSingleValueAlarms();
	void 	clearInopAlarms();

	void 	removeMuteTechAlarm(INT16 channel, AlarmId id);
	void    clearAllMuteTechAlarms();

	bool 	isMuteTechAlarm(AlarmId id);
	bool 	isMuteTechAlarmExist(INT16 channel, AlarmId id);
	void 	insertMuteTechAlarm(INT16 channel, AlarmId id);

	bool 	isVisualOnlyAlarm(AlarmId alarm_id);
	void 	setAcknowledged(bool ack);
	bool    isPhysicalAlarmExisted();

	void 	setNewPatient();

	size_t  getAlarmGenerateTickCout(INT16 channel, AlarmId id);
private:
	ALARM_MAP			alarmsMap;
	bool				isLowPowerSilence;

	MUTE_TECH_VEC muteTechAlarmsVec;

};


#endif /* ALARMDISPATCH_H_ */
