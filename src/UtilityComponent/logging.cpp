/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	logging.cpp
 * File Path:   
 * Author:		Richard Xie
 * Version:		1.0
 * Description: log function file
 *
 *
 * History:
 *  Date		    Author			CR number	        CR Title
 */

#include "logging.hpp"
using namespace std;


OperationLog::OperationLog()
{

}

INT8 OperationLog::Log(INT8U* ptr)
{

    if(nullptr == ptr)
        return 1;


    return 0;
}

INT32U OperationLog::readLog(INT8U* ptr, INT32U readLength)
{
    INT32U iReadLength = 0;





    return iReadLength;
}


OperationLog* OperationLog::getInstance(void)
{
   static OperationLog *instance = nullptr;
   if (nullptr == instance)
    {
        instance = new OperationLog;
    }
    
    return instance;    
}






/*
*               ErrorLog implementation
*
*
*/
ErrorLog::ErrorLog()
{
   // instance = nullptr;

}

INT8 ErrorLog::Log(INT8U* ptr)
{
    if(nullptr == ptr)
        return 1;
    
    

    return 0;
}

INT32U ErrorLog::readLog(INT8U* ptr, INT32U readLength)
{
    INT32U iReadLength = 0;


    return iReadLength;
}

ErrorLog* ErrorLog::getInstance(void)
{
   static ErrorLog *instance = nullptr;
   if (nullptr == instance)
    {
        instance = new ErrorLog;
    }
    
    return instance;

}



/*
*               AlarmLog implementation
*
*
*/
AlarmLog::AlarmLog()
{
   // instance = nullptr;

}

INT8 AlarmLog::Log(INT8U* ptr)
{
    if(nullptr == ptr)
        return 1;
    
    

    return 0;
}

INT32U AlarmLog::readLog(INT8U* ptr, INT32U readLength)
{
    INT32U iReadLength = 0;


    return iReadLength;
}

AlarmLog* AlarmLog::getInstance(void)
{
   static AlarmLog *instance = nullptr;
   if (nullptr == instance)
    {
        instance = new AlarmLog;
    }
    
    return instance;

}