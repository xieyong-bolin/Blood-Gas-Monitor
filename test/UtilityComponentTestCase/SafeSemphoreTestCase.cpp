/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	SafeSemphoreTestCase
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
#include "SafeSemphore.hpp"

TEST(SafeSemphoreTestCase, SafeSemphorecreateSemadefault)
{
    SafeSemphore testObjective;

    EXPECT_NE(-1, testObjective.createSema());

}


TEST(SafeSemphoreTestCase, SafeSemphorecreateSemaWithRightArguments)
{
    SafeSemphore testObjective;

    EXPECT_NE(-1, testObjective.createSema(100, 200));

}



TEST(SafeSemphoreTestCase, SafeSemphorecreateSemaWithIncorrectArguments)
{
    SafeSemphore testObjective;

    EXPECT_EQ(-1, testObjective.createSema(1000, 200));

}


TEST(SafeSemphoreTestCase, SafeSemphorecreateSemaAndDestroySemaSuccess)
{
    SafeSemphore testObjective;

    EXPECT_NE(-1, testObjective.createSema());

    EXPECT_NE(-1, testObjective.destroySema());

}


TEST(SafeSemphoreTestCase, SafeSemphoreDestroySemaUnsuccess)
{
    SafeSemphore testObjective;

    EXPECT_EQ(-1, testObjective.destroySema());

}


TEST(SafeSemphoreTestCase, SafeSemphorePutSemaUnsuccess)
{
    SafeSemphore testObjective;

    EXPECT_EQ(-1, testObjective.putSema());

}


TEST(SafeSemphoreTestCase, SafeSemphorePutSemaSuccess)
{
    SafeSemphore testObjective;

    EXPECT_NE(-1, testObjective.createSema());
    EXPECT_NE(-1, testObjective.putSema());

}