/*
 * CSafeSemphore.cpp
 *
 *  Created on: Jan 15, 2022
 *      Author: 
 */

#include "SafeSemphore.hpp"
#include <stdio.h>

using namespace std;

SafeSemphore::SafeSemphore()
{
	count=0;
	maxCount = SEMAPHORE_MAX_COUNT;
	init = false;
}

SafeSemphore::~SafeSemphore()
{
	destroySema();
}

INT32 SafeSemphore::createSema(INT32U initCountValue, INT32U maxCountValue)
{
    INT32 ret = -1;

    if (init)
    	return ret;

    if (initCountValue > maxCountValue)
        return ret;
	pthread_mutexattr_t mattr;
	pthread_mutexattr_init(&mattr);
	pthread_mutexattr_setrobust_np(&mattr, PTHREAD_MUTEX_ROBUST_NP);
	pthread_mutexattr_settype(&mattr, PTHREAD_MUTEX_RECURSIVE);
    ret = pthread_mutex_init(&mutex, &mattr);
    pthread_mutexattr_destroy(&mattr);
	if ( ret )
		printf("cannot create semaphore (mutex) %d\n", ret);

	pthread_condattr_t condattr;
	pthread_condattr_init(&condattr);
	ret = pthread_condattr_setclock(&condattr, CLOCK_MONOTONIC);
	if ( ret )
		printf("cannot create semaphore (setclock) %d\n", ret);

    ret = pthread_cond_init(&cond, &condattr);
    pthread_condattr_destroy(&condattr);
    if ( ret )
    	printf("cannot create semaphore (condition) %d\n", ret);

    count 		= initCountValue;
    maxCount  = maxCountValue;
    init 		= true;
    return ret;
}

INT32 SafeSemphore::destroySema()
{
	INT32 ret = -1;

	if ( !init )
		return ret;

	ret = pthread_cond_destroy(&cond);
	ret = pthread_mutex_destroy(&mutex);

	init = false;
    return ret;
}

INT32 SafeSemphore::putSema()
{
	INT32 ret = -1;

	if ( !init )
		return ret;

    if (int err = pthread_mutex_lock(&mutex))
    {
    	printf("cannot signal semaphore (lock) %d\n", err);
    	return ret;
    }

    if (count < maxCount)
    {
        ++count;
    }
    else
    {
        pthread_mutex_unlock(&mutex);
        printf("cannot signal semaphore: count would exceed maximum. count_ = %d, max_count_ = %d\n", count, maxCount);
        return ret;
    }

    ret = pthread_cond_signal(&cond);

    pthread_mutex_unlock(&mutex);

    return ret;
}

INT32 SafeSemphore::getSema(INT32U milliSeconds/*=INFINITE*/)
{
	INT32 ret = -1;

	if ( !init )
		return ret;

	if ( INFINITE == milliSeconds )
	{
	    if (int err = pthread_mutex_lock(&mutex))
	        printf("wait for semaphore failed (lock) %d\n", err);
	    while (count < 1)
	    {
	        if (int err = pthread_cond_wait(&cond, &mutex))
	        {
	            pthread_mutex_unlock(&mutex);
	            printf("wait for semaphore failed %d\n", err);
	            return ret;
	        }
	    }
	    --count;
	    pthread_mutex_unlock(&mutex);
	    return 0;
	}
	else
	{
		//!!! USE MONOTONIC for safe.
		struct timespec tv;
		clock_gettime(CLOCK_MONOTONIC, &tv);
	    tv.tv_sec  += milliSeconds / 1000;
	    tv.tv_nsec += (milliSeconds % 1000)*1000000;
	    if (tv.tv_nsec >= 1000000000)
	    {
	    	tv.tv_nsec -= 1000000000;
	    	tv.tv_sec++;
	    }
	    if (int err = pthread_mutex_lock(&mutex))
	        printf("wait for semaphore failed (lock) %d\n", err);

	    int rc = 0;
	    while (count < 1)
	    {
	        if ((rc = pthread_cond_timedwait(&cond, &mutex, &tv)))
	        {
	            if (rc == ETIMEDOUT)
	            	break;
	            pthread_mutex_unlock(&mutex);
	            printf("cannot wait for semaphore %d\n", rc);
	            return -1;
	        }
	    }
	    //if we got a signal, decrease the count_,
	    //if timeout, do nothing
	    if (rc == 0)
	    	--count;
	    pthread_mutex_unlock(&mutex);
	    return (rc == 0) ? 0 : -1;
	}
}
