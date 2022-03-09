/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	ParameterModule.hpp
 * File Path:
 * Author:		Richard Xie
 * Version:		1.0
 * Description:
 *
 * History:
 *  Date		Author			CR number	CR Title
 */

#ifndef PARAMETERMODULE_H_
#define PARAMETERMODULE_H_

#include "IDeviceModule.hpp"
using namespace std;

class ParameterModule : public IDeviceModule
{
private:
    /* data */
public:
    ParameterModule ();
    ~ParameterModule ();

    virtual INT8 shakeHand();  //connect to main board
    virtual INT8 initModule(); //
    virtual INT8 sendMessage();
    virtual INT8 receiveMesaage();
    virtual INT8 selftest();
    virtual INT8 process();
};

#endif