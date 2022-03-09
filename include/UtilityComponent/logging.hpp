/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	logging.hpp
 * File Path:   
 * Author:		Richard Xie
 * Version:		1.0
 * Description: log function head file
 *
 *
 * History:
 *  Date		    Author			CR number	        CR Title
 */

#ifndef LOGGING_H_
#define LOGGING_H_

#include <memory>
#include "datatype.h"
#include <vector>
#include <time.h>
using namespace std;

typedef struct LOGINFO
{
    string context;
    time_t time;
}LogInfo, *pLogInfo;

/*

interface for all logs

*/
class ILogging
{
private:
    /* data */
    std::vector<LogInfo> logInfo;
public:
    ILogging(/* args */){}
    virtual ~ILogging() {}
public:
    virtual INT8 Log(INT8U* ptr) = 0;
    virtual INT32U readLog(INT8U* ptr, INT32U readLength) = 0;
};

/*

operation log, call the function to log a message while user operate the system

*/
class OperationLog : public ILogging
{
private:
    /* data */
    OperationLog(/* args */);       
public:
   
    virtual ~OperationLog(){}
public:
    virtual INT8 Log(INT8U* ptr);
    virtual INT32U readLog(INT8U* ptr, INT32U readLength);

    static OperationLog* getInstance(void);
};

/*

ErrorLog log, call the function to log a message while system error

*/
class ErrorLog:public ILogging
{

public:
    /* data */
    ErrorLog(/* args */);
public:
   
   virtual ~ErrorLog(){}
public:
    virtual INT8 Log(INT8U* ptr);
    virtual INT32U readLog(INT8U* ptr, INT32U readLength);
    static ErrorLog* getInstance(void);
};




class AlarmLog:public ILogging
{

public:
    /* data */
    AlarmLog(/* args */);
public:
   
   virtual ~AlarmLog(){}
public:
    virtual INT8 Log(INT8U* ptr);
    virtual INT32U readLog(INT8U* ptr, INT32U readLength);
    static AlarmLog* getInstance(void);
};


#endif
