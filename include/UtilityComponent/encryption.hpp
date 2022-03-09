/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	encryption.hpp
 * File Path:   
 * Author:		Richard Xie
 * Version:		1.0
 * Description: encryption and decryption head file
 *
 *
 * History:
 *  Date		    Author			CR number	        CR Title
 */

#ifndef ENCRYPTION_H_
#define ENCRYPTION_H_

#include "datatype.h"
#include <string>

class encryption
{
public:
    encryption(/* args */){}
    ~encryption(){}
    encryption getInstance(void);

    std::string  encryptString(std::string stringContext);
    INT32   encryptFile(const std::string fileName);
    std::string  decryptString(std::string stringContext);
    INT32   decryptFile(const std::string fileName);
private:
    /* data */

};




#endif