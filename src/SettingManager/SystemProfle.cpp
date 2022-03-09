/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	SystemProfile.cpp
 * File Path:
 * Author:		Richard Xie
 * Version:		1.0
 * Description:
 *
 * History:
 *  Date		Author			CR number	CR Title
 */
#include <memory.h>
#include "SystemProfile.hpp"

SystemProfile::SystemProfile(/* args */)
{
    loadData();
}

SystemProfile::~SystemProfile()
{
}


void SystemProfile::loadData()
{
    loadSystemProfile();
    loadEEPROM();
}


void SystemProfile::saveData()
{
    saveSystemProfile();
    saveEEPROM();
}


void SystemProfile::loadSystemProfile()
{

}


void SystemProfile::saveSystemProfile()
{

}


void SystemProfile::loadEEPROM()
{

}


void SystemProfile::saveEEPROM()
{

}


LanguageId SystemProfile::getSystemLanguage()
{
    return systemProfileData.languageId;
}


void SystemProfile::setSystemLanguage(LanguageId id)
{
    systemProfileData.languageId = id;
}


INT16U* SystemProfile::getIpAddress()
{
    return eeprom.ipAddress;
}


INT8 SystemProfile::setIpAddress(INT16U* ipAddressString)
{
    memcpy(eeprom.ipAddress, ipAddressString, sizeof(eeprom.ipAddress));
}