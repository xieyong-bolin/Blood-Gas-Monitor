/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	AlarmManager.hpp
 * File Path:
 * Author:		Richard Xie
 * Version:		1.0
 * Description:
 *
 * History:
 *  Date		Author			CR number	CR Title
 */


#ifndef ALARMMANAGER_H_
#define ALARMMANAGER_H_

#include "AlarmDefines.hpp"
#include "WorkThread.hpp"


class AlarmManager : public WorkThread
{
private:
    AlarmManager();
public:
    
    virtual ~AlarmManager();
    static AlarmManager* getInstance();
    void manageAlarm();
protected:
	// You must implement this method
    INT32U run();

private:


};



#endif