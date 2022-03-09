/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	SystemProfile.hpp
 * File Path:
 * Author:		Richard Xie
 * Version:		1.0
 * Description:
 *
 * History:
 *  Date		Author			CR number	CR Title
 */

#ifndef SYSTEMPROFILE_H__
#define SYSTEMPROFILE_H__

#include "datatype.h"
#include "SystemDataDef.hpp"
#include <string>
using namespace std;


class SystemProfile
{

public:
    SystemProfile(/* args */);
    ~SystemProfile();

    void loadData();
    void saveData();
    
private:
    void loadSystemProfile();
    void saveSystemProfile();

    void loadEEPROM();
    void saveEEPROM();

    LanguageId getSystemLanguage();
    void setSystemLanguage(LanguageId id);

    INT16U *getIpAddress();
    INT8 setIpAddress(INT16U *ipAddressString);

private:
    SystemProfileData   systemProfileData;
    EEPROM              eeprom;
    std::string         currentProfile;
   // std::string         
};






#endif