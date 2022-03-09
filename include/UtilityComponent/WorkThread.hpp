/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	WorkThread.h
 * File Path:
 * Author:		Richard Xie
 * Version:		1.0
 * Description:
 *
 * History:
 *  Date		Author			CR number	CR Title
 */

#ifndef WORKTHREAD_H_
#define WORKTHREAD_H_


#include <pthread.h>
#include "SafeSemphore.hpp"
#include "AutoLock.hpp"

constexpr INT32 MAX_CLASS_NAME	=	32;

class WorkThread
{
public:
	WorkThread(const char* name, INT32 priorityId = DEFAULT_THREAD_PRIORITY);
	virtual ~WorkThread();

    // These take ordered integers
	bool setPolicy(INT32 newPolicy);
	bool setPriority(INT32 newPriority);
	bool validPriority( INT32 policy, INT32& priority );
	INT32 getPriority(void);
	bool start(void);
	bool stop(bool async = false, INT32U dwWaitTimeout = INFINITE);
	bool isRunning(void) const __attribute__((no_instrument_function));
	bool isStopping(void) const __attribute__((no_instrument_function));
	bool isSuspend(void) const __attribute__((no_instrument_function));
	virtual void Suspend();
	virtual void resume();
	virtual void updateTime() __attribute__((no_instrument_function));
protected:
	// You must implement this method
    virtual INT32U run() = 0;

    // Derived classes may override this method to add to
    // the chain. The virtual RunThread() is called last.
    virtual void runThreadOuter(void);

	volatile bool	running;
	volatile bool   suspend;
	volatile bool   stopping;
	pthread_t		thread;
	INT32U			quitId;
	INT32U			priority;

	// Utility function that starts RunThread()
	static void* threadProc(void* pParam);

	// Thread name
	INT8 				className[MAX_CLASS_NAME];
	SafeSemphore 		syncSema;
	MutexLightLock 		apiMutex;
	INT32               lastUpdateTick;
};

#endif /* WORKTHREAD_H_ */
