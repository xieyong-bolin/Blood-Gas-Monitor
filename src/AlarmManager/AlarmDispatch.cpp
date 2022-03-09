/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	AlarmDispatch.cpp
 * File Path:
 * Author:		Richard Xie
 * Version:		1.0
 * Description:
 *
 * History:
 *  Date		Author			CR number	CR Title
 */

#include <stdlib.h>
#include "AlarmDispatch.hpp"
#include "AlarmManager.hpp"
#include "AutoLock.hpp"


constexpr INT32 MinAlarmDuration	=	10000;
AlarmMap alarmListMap[static_cast<int>(AlarmId::AlarmNum)] = {
{AlarmId::UnkownId,         AlarmType::other,               AlarmPriority::unknowPriority},
{AlarmId::PHHigh,           AlarmType::physiological,       AlarmPriority::middlePriority},
{AlarmId::PHLow,            AlarmType::physiological,       AlarmPriority::middlePriority},
{AlarmId::So2High,          AlarmType::physiological,       AlarmPriority::middlePriority},
{AlarmId::So2Low,           AlarmType::physiological,       AlarmPriority::middlePriority},
{AlarmId::SPCO2High,        AlarmType::physiological,       AlarmPriority::middlePriority},
{AlarmId::SPCO2Low,         AlarmType::physiological,       AlarmPriority::middlePriority},
{AlarmId::TempHigh,         AlarmType::physiological,       AlarmPriority::middlePriority},
{AlarmId::TempLow,          AlarmType::physiological,       AlarmPriority::middlePriority}
};

AlarmDispatch::AlarmDispatch()
{
	alarmsMap.clear();
	isLowPowerSilence = false;
}

AlarmDispatch::~AlarmDispatch()
{
	ALARM_ITER alarm_iter = alarmsMap.begin();
	for ( ; alarm_iter!=alarmsMap.end(); ++alarm_iter)
	{
		alarm_iter->second.clear();
	}
	alarmsMap.clear();
}

bool AlarmDispatch::addAlarm( ALARM alarm )
{
	auto channel = alarm.channel;

	ALARM_ITER iter = alarmsMap.find(channel);
	//a new channel, it is ok that we never delete channel.
	if (iter == alarmsMap.end())
	{
		std::list<AlarmItem> list;
		AlarmItem alarmItem(alarm);
		list.push_back(alarmItem);
		alarmsMap.insert( ALARM_MAP::value_type( channel, list ) );

		// A new alarm arrived
		if( alarmItem.getAlarmId() == AlarmId::BatteryLow)
			isLowPowerSilence = false;

		if( isMuteTechAlarm( alarmItem.getAlarmId() ) )
			removeMuteTechAlarm( alarmItem.getChannel(), alarmItem.getAlarmId() );
	}
	else //the channel was insert before
	{
		std::list<AlarmItem>::iterator iter = alarmsMap[channel].begin();
		for (; iter != alarmsMap[channel].end(); ++iter)
		{
			if (alarm.channel == (*iter).getChannel()
					&& alarm.id == (*iter).getAlarmId())
			{
				break;
			}
		}
		//we find it.
		if ( iter != alarmsMap[channel].end() )
		{
			// The alarm was deleted before, but because it is a latched alarm
			// or register/unregister in a short time, it is not really removed.
			// Only a flag was set.
			if ((*iter).getStatus())
			{
				ALARM alarm = (*iter).getAlarm();
				//remove it
				alarmsMap[channel].erase(iter);
			}else
			{
				//repeat to add, do nothing
				return false;
			}
		}

		// A new alarm arrived
		if( alarm.id == AlarmId::BatteryLow )
			isLowPowerSilence = false;

		if( isMuteTechAlarm( alarm.id  ) )
			removeMuteTechAlarm( channel, alarm.id  );

		//Add it to the list.
		AlarmItem alarmItem(alarm);
		alarmsMap[channel].push_back(alarmItem);
	}
	return true;
}

bool AlarmDispatch::removeAlarm( INT16 channel, AlarmId id, bool forceDelete )
{
	if (!isChannelExisted(channel))
		return false;

	std::list<AlarmItem>::iterator iter = alarmsMap[channel].begin();
	for( ; iter != alarmsMap[channel].end(); ++iter )
	{
		if( channel == (*iter).getChannel() &&
			id == (*iter).getAlarmId() )
		{
			break;
		}
	}

	if( iter == alarmsMap[channel].end() )
		return false;
	else
	{
		if (!forceDelete)
		{
			// Latched alarm should not be deleted by unregister
			if ((*iter).isLatched())
			{
				if (!(*iter).isSilenced())
				{
					(*iter).setStatus(true);
					return false;
				}
			}

			//if it has not reach its MinAlarmDuration, just set the delete flag.
			if( abs( int(getTickCount() - (*iter).getTickCount()) ) < MinAlarmDuration )
			{
				if (!(*iter).getStatus())
				{
					(*iter).setStatus(true);
					return false;
				}else //it has been deleted
				{
					return false;
				}
			}
		}

		alarmsMap[channel].erase(iter);
		return true;
	}
}

void AlarmDispatch::deleteObsolete()
{
	ALARM_ITER alarmIter = alarmsMap.begin();
	for ( ; alarmIter!=alarmsMap.end(); ++alarmIter)
	{
		auto channel = alarmIter->first;
		std::list<AlarmItem>::iterator iter = alarmsMap[channel].begin();
		for ( ; iter != alarmsMap[channel].end(); )
		{
			// The alarm is unregistered and it is not latched
			if ((*iter).getStatus())
			{
				if (getTickCount() - (*iter).getTickCount() >= MinAlarmDuration)
				{
					if (!(*iter).isLatched())
					{
						ALARM alarm = (*iter).getAlarm();
						
//						cout << "delete no latched alarm " << (*iter).getAlarmId() << endl;
						iter = alarmsMap[channel].erase(iter);
						continue;
					}else //latched alarm
					{
						if ((*iter).isSilenced())
						{
							ALARM alarm = (*iter).getAlarm();
							
							//cout << "delete silenced alarm " << (*iter).getAlarmId() << endl;
							iter = alarmsMap[channel].erase(iter);
							continue;
						}
					}
				}
			}
			++iter;
		}
	}
}

void AlarmDispatch::reset()
{
	ALARM_ITER listIter = alarmsMap.begin();
	for (; listIter!=alarmsMap.end(); ++listIter)
	{
		std::list<AlarmItem>::iterator iter = listIter->second.begin();
		for (; iter != listIter->second.end(); ++iter)
		{
			ALARM alarm = (*iter).getAlarm();
		//	ALARMMGR_PTR->set_register_status(alarm.channel, alarm.id, false);
		//	ALARMMGR_PTR->add_alarm_log(alarm, false);
		}
		listIter->second.clear();
	}

	alarmsMap.clear();
}

bool AlarmDispatch::isAlarmExist( INT16 channel, AlarmId id )
{
	if (!isChannelExisted(channel))
		return false;

	std::list<AlarmItem>::iterator iter = alarmsMap[channel].begin();
	for( ; iter != alarmsMap[channel].end(); ++iter )
	{
		if( channel == (*iter).getChannel() &&
			id == (*iter).getAlarmId() )
		{
			break;
		}
	}

	return ( iter != alarmsMap[channel].end() ? true : false );
}

void AlarmDispatch::getHighestAlarmPri(
	INT16& audioPri,
	INT16& msgPri,
	INT16& ledPri)
{
	INT16 priTmp = static_cast<INT16>(AlarmPriority::unknowPriority);

	ALARM_ITER alarmIter = alarmsMap.begin();
	for ( ; alarmIter!=alarmsMap.end(); ++alarmIter)
	{
		short channel = alarmIter->first;
		std::list<AlarmItem>::iterator iter = alarmsMap[channel].begin();
		for ( ; iter != alarmsMap[channel].end(); ++iter )
		{
			priTmp = static_cast<INT16>((*iter).getPriority());
			if(priTmp > msgPri)
			{
				msgPri = priTmp;
			}

			if(priTmp > audioPri)
			{
				AlarmId alarmId = (*iter).getAlarmId();
				if (isVisualOnlyAlarm(alarmId))
				{
					continue;
				}

				if ( (isLowPowerSilence ) && (*iter).getAlarmId() == AlarmId::BatteryLow )
				{
					continue;
				}
				else if ( (*iter).getAlarmId() == AlarmId::BatteryVeryLow)
				{
					continue;
				}
				else if( isMuteTechAlarmExist((*iter).getChannel(), (*iter).getAlarmId()) )
				{
					continue;
				}
				else
				{
					audioPri = priTmp;
				}
			}
		}
	}

	ledPri = msgPri;
}

void AlarmDispatch::getAlarms( INT16 channel, AlarmPriority priority, std::vector<AlarmItem>& alarms )
{
	if (!isChannelExisted(channel) || alarmsMap[channel].empty())
	{
		return ;
	}

	std::list<AlarmItem>::iterator iter = alarmsMap[channel].begin();
	for( ; iter != alarmsMap[channel].end(); ++iter )
	{
		if( priority == (*iter).getPriority() )
		{
			alarms.push_back( *iter );
		}
	}
}

void AlarmDispatch::getAlarms( AlarmPriority priority, std::vector<AlarmItem>& alarms )
{
	ALARM_ITER alarmIter = alarmsMap.begin();
	for ( ; alarmIter!=alarmsMap.end(); ++alarmIter)
	{
		INT16 channel = alarmIter->first;
		getAlarms(channel, priority, alarms);
	}
}

//Get all alarms which are flashing.
void AlarmDispatch::getAlarms( std::vector<AlarmItem>& alarms )
{
	for(INT16 i = static_cast<INT16>(AlarmPriority::lowPriority); i <= static_cast<INT16>(AlarmPriority::highPriority); i++ )
	{
		getAlarms(static_cast<AlarmPriority>(i), alarms);
	}
}

bool AlarmDispatch::getAlarmInfo(
	INT16 channel,
	AlarmId id,
	ALARM& alarm )
{
	if (!isChannelExisted(channel))
		return false;

	std::list<AlarmItem>::iterator iter = alarmsMap[channel].begin();
	for( ; iter != alarmsMap[channel].end(); ++iter )
	{
		if( channel == (*iter).getChannel() &&
			id == (*iter).getAlarmId() )
		{
			alarm = (*iter).getAlarm();
			return true;
		}
	}
	return false;
}


bool AlarmDispatch::isChannelExisted(short channel)
{
	ALARM_ITER iter = alarmsMap.find(channel);
	return  (iter == alarmsMap.end() ? false : true);
}


void AlarmDispatch::clearLatchedAlarm()
{
	ALARM_ITER alarmIter = alarmsMap.begin();

	for ( ; alarmIter!=alarmsMap.end(); ++alarmIter )
	{
		short channel = alarmIter->first;
		std::list<AlarmItem>::iterator iter = alarmsMap[channel].begin();
		for( ; iter != alarmsMap[channel].end(); )
		{
			if ((*iter).isLatched())
			{
				(*iter).setSilenced(true);

				if ((*iter).getStatus())
				{
					ALARM alarm = (*iter).getAlarm();
					iter = alarmsMap[channel].erase(iter);
					continue;
				}
			}
			++iter;
		}
	}
}

void AlarmDispatch::clearSingleValueAlarms()
{

}

void AlarmDispatch::clearInopAlarms()
{
	
}


void AlarmDispatch::removeMuteTechAlarm(INT16 channel, AlarmId id)
{
	for(size_t i = 0; i < muteTechAlarmsVec.size(); i++)
	{
		if( muteTechAlarmsVec[i].first == channel
				&& muteTechAlarmsVec[i].second == id )
		{
			muteTechAlarmsVec.erase( muteTechAlarmsVec.begin()+i );
			return;
		}
	}
}


void AlarmDispatch::clearAllMuteTechAlarms()
{
	muteTechAlarmsVec.clear();
}


void AlarmDispatch::insertMuteTechAlarm(INT16 channel, AlarmId id)
{
//	if( !isMuteTechAlarmExist(channel, id) )
//		muteTechAlarmsVec.push_back(std::make_pair<INT16, AlarmId>(channel, id));
}


bool AlarmDispatch::isMuteTechAlarmExist(INT16 channel, AlarmId id)
{
	for(size_t i = 0; i < muteTechAlarmsVec.size(); i++)
	{
		if( muteTechAlarmsVec[i].first == channel
				&& muteTechAlarmsVec[i].second == id )
			return true;
	}
	return false;
}

bool AlarmDispatch::isMuteTechAlarm(AlarmId id)
{

}

bool AlarmDispatch::isVisualOnlyAlarm(AlarmId alarmId)
{

	return false;

}

void AlarmDispatch::setAcknowledged(bool ack)
{
	ALARM_ITER alarmIter = alarmsMap.begin();
	for ( ; alarmIter!=alarmsMap.end(); ++alarmIter )
	{
		short channel = alarmIter->first;
		std::list<AlarmItem>::iterator iter = alarmsMap[channel].begin();
		for( ; iter != alarmsMap[channel].end(); ++iter )
		{
			(*iter).setAcknowledged(ack);
		}
	}
}

bool AlarmDispatch::isPhysicalAlarmExisted()
{
	
	return false;
}

//while set new patient, all current alarm information should clean
void AlarmDispatch::setNewPatient()
{
	
}

size_t AlarmDispatch::getAlarmGenerateTickCout(INT16 channel, AlarmId id)
{
	size_t retval = -1;


	return retval;
}

