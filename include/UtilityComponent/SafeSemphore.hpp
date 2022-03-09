/*
 * CSafeSemphore.h
 *
 *  Created on: Jan 15, 2021
 *      Author: 
 *      The main purpose to create this class is to make sure it work well when system time changes.
 */

#ifndef SAFESEMPHORE_H_
#define SAFESEMPHORE_H_

#include <stdint.h>
#include <errno.h>
#include <pthread.h>
#include <iostream>
#include "datatype.h"

constexpr INT32U SEMAPHORE_MAX_COUNT = 256;


class SafeSemphore
{

public:
	SafeSemphore();
	virtual ~SafeSemphore();

	INT32 createSema(INT32U initCount=0, INT32U maxCount = SEMAPHORE_MAX_COUNT);
	INT32 destroySema();
	INT32 putSema();
	INT32 getSema(INT32U milliSeconds=INFINITE) __attribute__((no_instrument_function));

private:
    volatile int32_t    count;
    int32_t             maxCount;
    pthread_mutex_t 	mutex;
    pthread_cond_t  	cond;
    bool				init;
};

#endif /* SAFESEMPHORE_H_ */
