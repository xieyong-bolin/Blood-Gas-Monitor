/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	MainScreen.hpp
 * File Path:
 * Author:		Richard Xie
 * Version:		1.0
 * Description: application program entry
 *
 *
 * History:
 *  Date		    Author			CR number	        CR Title
 */

#ifndef IWINDOWS_H_
#define IWINDOWS_H_

#include <QtGui/QWidget>

namespace BMUsrInterface
{
class IWindow
{
public:
    IWindow(QWidget* widget);
    virtual ~IWindow();
    virtual int windowProc(UINT message, WPARAM wparam, LPARAM lparam) = 0;
    QWidget* getWidget() { return this; }
    virtual bool getSelected() { return selected; }

protected:
    QWidget* this;
    bool selected;
};

}    // namespace BMUsrInterface

#endif