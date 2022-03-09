
///////////////////////////////////////////////////////////
//  SettingManager.h
//  Implementation of the Class SettingManager
//  Created on:      22-Feb-2022 11:02:00 AM
//  Original author: xiey3
///////////////////////////////////////////////////////////

#if !defined(EA_A3C6307D_467B_4ecb_9107_5317E8935D29__INCLUDED_)
#define EA_A3C6307D_467B_4ecb_9107_5317E8935D29__INCLUDED_

#include "AlarmLimitSetting.hpp"
#include "Patient.hpp"
#include "SystemProfile.hpp"

class SettingManager
{
private:
	SettingManager();
public:

	virtual ~SettingManager();
    static SettingManager* getInstance();
    INT8 saveSettingData();
    INT8 loadSettingData();

    INT8 getPatientInfo(PATIENT &pat);
    INT8 setPatientInfo(PATIENT &pat);

    INT8 newPatient();
private:
	AlarmLimitSetting alarmLimitSetting;
	Patient patient;
	SystemProfile systemProfile;
    
};
#endif // !defined(EA_A3C6307D_467B_4ecb_9107_5317E8935D29__INCLUDED_)
