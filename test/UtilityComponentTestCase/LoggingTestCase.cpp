/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	LoggingTestCase
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
#include "logging.hpp"


TEST(OperationLogTest, HandleLogInformationPointNullInuput)
{

    OperationLog *instance = OperationLog::getInstance();

    EXPECT_NE(nullptr, instance);
    EXPECT_EQ(1, instance->Log(nullptr));

}

TEST(OperationLogTest, HandleLogInformation)
{


}


TEST(ErrorLogTest, NewObjective)
{
    ErrorLog *ptr = ErrorLog::getInstance();

    EXPECT_TRUE(nullptr != ptr);

}