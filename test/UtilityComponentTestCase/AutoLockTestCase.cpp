/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	AutoLockTestCase
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
#include "AutoLock.hpp"


TEST(MutexLightLockTestCase, MutexLightLockTryLock)
{
    MutexLightLock testObjective;

    EXPECT_EQ(0, testObjective.tryLock());

}

TEST(MutexLightLockTestCase, MutexLightLockLock)
{
    MutexLightLock testObjective;

    EXPECT_EQ(0, testObjective.lock());
}



TEST(MutexLightLockTestCase, MutexLightLockUnlock)
{
    MutexLightLock testObjective;

    EXPECT_EQ(1, testObjective.unlock());
}


TEST(MutexLightLockTestCase, MutexLightLockFullFollow)
{
    MutexLightLock testObjective;

    EXPECT_EQ(0, testObjective.tryLock());
    EXPECT_EQ(0, testObjective.lock());
    EXPECT_EQ(0, testObjective.tryLock());
    EXPECT_EQ(0, testObjective.unlock());
}




/////
TEST(MutexHeavyLockTestCase, MutexHeavyLockTrylock)
{
    MutexHeavyLock testObjective("test");

    EXPECT_EQ(0, testObjective.tryLock());

}

/*
TEST(MutexHeavyLockTestCase, MutexHeavyLockLock)
{
    MutexHeavyLock testObjective("test");

    EXPECT_EQ(0, testObjective.lock());
    EXPECT_EQ(0, testObjective.lock());
}
*/


TEST(MutexHeavyLockTestCase, MutexHeavyLockUnlock)
{
    MutexHeavyLock testObjective("test");

    EXPECT_EQ(0, testObjective.unlock());
}
