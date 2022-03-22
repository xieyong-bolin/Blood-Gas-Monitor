/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	AlarmDispatchTestCase.cpp
 * File Path:
 * Author:		Richard Xie
 * Version:		1.0
 * Description: unit test case
 *
 *
 * History:
 *  Date		    Author			CR number	        CR Title
 */

#include "AlarmDispatch.hpp"
#include "gtest/gtest.h"


TEST(AlarmDispatchTestCase, AlarmDispatchFunctionsetAcknowledgedTest)
{
    AlarmDispatch objective;

    EXPECT_TRUE(objective.setAcknowledged(false));
}