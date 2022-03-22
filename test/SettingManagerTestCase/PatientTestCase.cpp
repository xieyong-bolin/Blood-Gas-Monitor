/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	PatientTestCase
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
#include "Patient.hpp"


TEST(PatientTestCase, PatientWeightGetAndSet)
{
    Patient objective;

    objective.setWeight(10);

    EXPECT_EQ(10, objective.getWeight());

}