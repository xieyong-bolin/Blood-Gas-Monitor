/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	SystemDataDef.hpp
 * File Path:
 * Author:		Richard Xie
 * Version:		1.0
 * Description:
 *
 * History:
 *  Date		Author			CR number	CR Title
 */

#ifndef SYSTEMDATADEF_H__
#define SYSTEMDATADEF_H__
#include <string>
using namespace std;

enum class LayoutId
{
    Trend = 0,
    BigNum,
    TrendTable,
    DashBoard,
    RelationshipTree,
    Ecmo
};

enum class LanguageId
{
    English = 0,
    Chinese,
    Spain,
    Russian,
    Franch
};


typedef struct Systemprofiledata
{
    /* data */
   // INT32U 
    std::string deviceName;
    LayoutId    layout;
    LanguageId  languageId;


}SystemProfileData, *pSystemProfileData;



typedef struct eeprom
{
    INT16U  ipAddress[8];
    INT16U  macAddress[16];
    INT32U  keycode[16];

}EEPROM, *pEEPROM;



#endif