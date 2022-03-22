/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	AlarmLimitSettingTestCase
 * File Path:   
 * Author:		Richard Xie
 * Version:		1.0
 * Description: unit test case
 *
 *
 * History:
 *  Date		    Author			CR number	        CR Title
 */

#include "gtest/gtest.h"
#include "AlarmLimitSetting.hpp"


TEST(AlarmLimitSettingTestCase, AlarmLimitSettingresetAlarmLimit)
{
    AlarmLimitSetting objective;

    EXPECT_EQ(0, objective.resetAlarmLimit());

}