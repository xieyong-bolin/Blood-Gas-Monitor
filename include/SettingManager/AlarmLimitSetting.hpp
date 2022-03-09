///////////////////////////////////////////////////////////
//  AlarmLimitSetting.h
//  Implementation of the Class AlarmLimitSetting
//  Created on:      22-Feb-2022 11:02:00 AM
//  Original author: xiey3
///////////////////////////////////////////////////////////

#if !defined(EA_289D2E72_BD4D_4825_918D_951AB83B5EDF__INCLUDED_)
#define EA_289D2E72_BD4D_4825_918D_951AB83B5EDF__INCLUDED_

#include "datatype.h"

using AlarmSystemSet = struct alarmsystemset
{
    INT8U alarmAudioLevel;
    INT32U maintenancePassWord;
    INT32U adminPassWord;
    
    /* data */
};


using AlarmLimitSet = struct alarmlimitset
{
    INT16U  So2LowLimit;
    INT16U  So2HighLimit;

    void init(void)
    {
        So2HighLimit = 100;
        So2LowLimit = 90;
    }

    /* data */
};

using AlarmSysSet = struct alarmsysset
{
    AlarmSystemSet alarmSystemSet;
    AlarmLimitSet  alarmLimitSet;
};


class AlarmLimitSetting
{

public:
	AlarmLimitSetting();
	virtual ~AlarmLimitSetting();

    INT8 loadAlarmSet();
    INT8 saveAlarmSet();

    INT8 resetAlarmLimit();
private:
    AlarmSysSet alarmSet;
};
#endif // !defined(EA_289D2E72_BD4D_4825_918D_951AB83B5EDF__INCLUDED_)
