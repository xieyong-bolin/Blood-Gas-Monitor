/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	MainScreen.hpp
 * File Path:
 * Author:		Richard Xie
 * Version:		1.0
 * Description:
 *
 *
 * History:
 *  Date		    Author			CR number	        CR Title
 */


#ifndef MAINSCREEN_H__
#define MAINSCREEN_H__

#include <QtWidgets/QApplication>
#include "datatype.h"

namespace BMUsrInterface
{
class MainScreen
{
private:
    /* data */
public:
    MainScreen(/* args */);
    ~MainScreen();
};


int startUpScreen(INT32 argc, INT8 **argv);


}    // namespace BMUsrInterface


#endif