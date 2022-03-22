/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	MainScreen.cpp
 * File Path:
 * Author:		Richard Xie
 * Version:		1.0
 * Description:
 *
 *
 * History:
 *  Date		    Author			CR number	        CR Title
 */
#include "MainScreen.hpp"

namespace BMUsrInterface
{
int startUpScreen(INT32 argc, INT8 **argv)
{
    QApplication screenInstance(argc, argv);

    return screenInstance.exec();
}

MainScreen::MainScreen() {}

MainScreen::~MainScreen() { return 1; }

}    // namespace BMUsrInterface