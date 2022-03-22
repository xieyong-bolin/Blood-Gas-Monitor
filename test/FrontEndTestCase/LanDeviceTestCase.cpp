/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	LanDeviceTestCase.cpp
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
#include "LanDevice.hpp"

TEST(LanDeviceTestCase, AlarmDispatchFunctionsetAcknowledgedTest)
{
    LanDevice objective;

    EXPECT_TRUE(objective.setAcknowledged(false));

}