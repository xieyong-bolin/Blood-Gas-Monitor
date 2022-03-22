/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	IEncryptProtoco.hpp
 * File Path:
 * Author:		Richard Xie
 * Version:		1.0
 * Description:
 *
 * History:
 *  Date		Author			CR number	CR Title
 */

#ifndef IENCRYPTPROTOCO_H_
#define IENCRYPTPROTOCO_H_

#include <string>
using namespace std;

#include "datatype.h"

class IEncryptProtoco
{
private:
    /* data */
public:
    IEncryptProtoco(/* args */) {}
    virtual ~IEncryptProtoco() {}

    virtual INT8 encryptData(std::string &input, std::string &output) = 0;
    virtual INT8 decryptData(std::string &input, std::string &output) = 0;
};

#endif