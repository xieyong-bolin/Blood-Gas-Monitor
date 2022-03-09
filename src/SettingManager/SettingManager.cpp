///////////////////////////////////////////////////////////
//  SettingManager.cpp
//  Implementation of the Class SettingManager
//  Created on:      22-Feb-2022 11:02:00 AM
//  Original author: xiey3
///////////////////////////////////////////////////////////

#include "SettingManager.hpp"


SettingManager::SettingManager()
{

}


SettingManager::~SettingManager()
{

}

SettingManager *SettingManager::getInstance()
{
    static SettingManager *instancePtr = nullptr;

    if (nullptr == instancePtr)
    {
        instancePtr = new SettingManager;
    }

    return instancePtr;
}

INT8 SettingManager::saveSettingData()
{
    patient.savePatient();
    systemProfile.loadData();
    alarmLimitSetting.loadAlarmSet();

    return 0;
}


INT8 SettingManager::loadSettingData()
{
    patient.loadPatient();
    systemProfile.saveData();
    alarmLimitSetting.saveAlarmSet();

    return 0;
}


INT8 SettingManager::getPatientInfo(PATIENT &pat)
{
    pat = patient.getPatientInfo();
    return 0;
}


INT8 SettingManager::setPatientInfo(PATIENT &pat)
{
    patient.setPatientInfo(pat);
    return 0;
}


INT8 SettingManager::newPatient()
{
    patient.clear();
    alarmLimitSetting.resetAlarmLimit();

    return 0;
}