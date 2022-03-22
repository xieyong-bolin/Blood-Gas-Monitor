/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	OperationInstanceTestCase.cpp
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
#include "OperationInstance.hpp"

TEST(OperationInstanceTestCase, AlarmDispatchFunctionsetAcknowledgedTest)
{

    EXPECT_TRUE(OperationInstance::getInstance()->clearData());
}