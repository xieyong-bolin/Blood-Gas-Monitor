/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	AutoLock.h
 * File Path:
 * Author:		Richard Xie
 * Version:		1.0
 * Description:
 *
 * History:
 *  Date		Author			CR number	CR Title
 */

#ifndef AUTOLOCK_H_
#define AUTOLOCK_H_

#include "datatype.h"
#include <pthread.h>

#define CMutex MutexLightLock

class MutexLock
{
public:
	MutexLock()	{}
	virtual ~MutexLock()	{}

	virtual INT32 tryLock() = 0;
	virtual INT32 lock() = 0;
	virtual INT32 unlock() = 0;
};

class MutexLightLock : public MutexLock
{
public:
	MutexLightLock()
	{
		pthread_mutexattr_t mattr;
		pthread_mutexattr_init(&mattr);
		pthread_mutexattr_setrobust_np(&mattr, PTHREAD_MUTEX_ROBUST_NP);
		pthread_mutexattr_settype(&mattr, PTHREAD_MUTEX_RECURSIVE);
		pthread_mutex_init(&mutexLock, &mattr);
		pthread_mutexattr_destroy(&mattr);
	}
	virtual ~MutexLightLock()	{ pthread_mutex_destroy(&mutexLock);			}

	virtual INT32 tryLock()		{ return pthread_mutex_trylock(&mutexLock);	}
	virtual INT32 lock()			{ return pthread_mutex_lock(&mutexLock);		}
	virtual INT32 unlock()		{ return pthread_mutex_unlock(&mutexLock);	}

private:
	pthread_mutex_t mutexLock;
};

class MutexHeavyLock : public MutexLock
{
public:
	MutexHeavyLock(const char* name);
	virtual ~MutexHeavyLock();

	virtual INT32 tryLock()		{ return pthread_mutex_trylock(mutexLock);	}
	virtual INT32 lock()			{ return pthread_mutex_lock(mutexLock);		}
	virtual INT32 unlock()		{ return pthread_mutex_unlock(mutexLock);		}

private:
	pthread_mutex_t* sharedMutexInit(pthread_mutex_t* pMutex);
	INT32 detatchFromSharedMem(pthread_mutex_t* pMutex, const char* pathName);
	pthread_mutex_t* getSharedMutex(const char* pathName);

private:
	pthread_mutex_t*	mutexLock;
	INT8				nameMember[256];
};

class AutoLock
{
public:
	AutoLock(MutexLock& lock);
	virtual ~AutoLock();

private:
	MutexLock& mutexLock;
};

class MicroportMutex
{
public:
	MicroportMutex(pthread_mutex_t *mutexT);
	virtual ~MicroportMutex();

private:
	pthread_mutex_t *mutexObj;
};

#endif /* AUTOLOCK_H_ */
