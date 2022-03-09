/*
 * TWorkThread.cpp
 *
 *  Created on: Jan 25, 2022
 *      Author:  Richard. Xie
 */

#include "logging.hpp"
#include "WorkThread.hpp"
#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include <memory.h>
#include <signal.h>
#include <errno.h>
#include <iostream>
#include <sys/syscall.h>
#include <unistd.h>
using namespace std;

constexpr INT32U MAX_DBG_MSG = 256;
constexpr INT32U THREAD_UPDATE_INTERVAL = 3000;

WorkThread::WorkThread(const char* name, INT32 priorityId)
{
	assert(name);
	running = false;
	suspend = false;
	stopping = false;
	quitId = 0;
	thread = 0;
	priority = priorityId;
	memset(className, 0, MAX_CLASS_NAME);
	snprintf(const_cast<char*>(className), MAX_CLASS_NAME,"%s",name);
	syncSema.createSema(0);
	lastUpdateTick = 0;
}

WorkThread::~WorkThread()
{
	syncSema.destroySema();
}

void WorkThread::updateTime()
{

}
/*****************************************************************
StartThread

	Create a new thread and start it
*****************************************************************/
bool WorkThread::start(void)
{
	if (isRunning())
	{
		std::cout << "The WorkThread( "<<className<<" ) is running!!" << std::endl;
		return false;
	}
	AutoLock lock(apiMutex);
	stopping = false;
	pthread_attr_t tattr;
	pthread_attr_init(&tattr);
#ifdef CROSS_COMPILE
	pthread_attr_setinheritsched(&tattr, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setscope(&tattr, PTHREAD_SCOPE_SYSTEM);
	pthread_attr_setschedpolicy(&tattr, SCHED_RR);
	struct sched_param param;
	validPriority( SCHED_RR, priority_ );
	param.sched_priority = priority_;
	pthread_attr_setschedparam(&tattr, &param);
#endif
	pthread_attr_setdetachstate(&tattr, PTHREAD_CREATE_JOINABLE);

	running = true;
	// Create the thread. This call should not really have any problems.
	if (0 != pthread_create(&thread, &tattr, threadProc, this))
	{
		printf("TWorkThread::start() - _beginthreadex failed!");
		running = false;
		pthread_attr_destroy(&tattr);
		return false;
	}

	pthread_attr_destroy(&tattr);

	std::cout << "####" << className << " started" << std::endl;
	return true;
}

bool WorkThread::stop(bool async, INT32U dwWaitTimeout)
{
	if (!isRunning())
	{
		std::cout << "The WorkThread( "<< className <<" ) is not running!!" << std::endl;
		return true;
	}
	if ( stopping )
	{
		std::cout << "The WorkThread( "<< className <<" ) is on stopping!!" << std::endl;
		return true;
	}

	AutoLock lock(apiMutex);
	stopping = true;
	if (!async)
	{
	    switch (syncSema.getSema(dwWaitTimeout))
	    {
	    case 0:
	    	pthread_join(thread, NULL);
	    	break;
	    case -1:
	    	std::cout<<"!!!Error:" << className << " stop timeout!!!"<<std::endl;
	    	pthread_detach(thread);
	        break;
		default:
			break;
	    }
	}
	else
	{
		pthread_detach(thread);
	}
	std::cout << "####" << className << " stopped" << std::endl;
	return true;
}

/*****************************************************************
IsRunning

	Check to see if the thread is currently running
*****************************************************************/
bool WorkThread::isRunning(void) const
{
	return running;
}


void* WorkThread::threadProc(void* pParam)
{
 	WorkThread *pThread = static_cast<WorkThread*>(pParam);
	if(nullptr == pThread)
		return nullptr;
 	printf("******thread started. %s, %ld******\n", pThread->className, syscall(SYS_gettid));

	pThread->runThreadOuter();

	printf("******thread stopped. %s, %ld******\n", pThread->className, syscall(SYS_gettid));

	pThread->running = false;
	pThread->syncSema.putSema();

	return static_cast<void*>(&pThread->quitId);
}

/*********************************************************************
RunThreadOuter - Non Virtual

    Derived classes can override this as long as they call the
    inherited RunThreadOuter().
*********************************************************************/
void WorkThread::runThreadOuter(void)
{
	quitId = run();
    // If you were overriding this method, you can add post-code here.
}

bool WorkThread::validPriority( INT32 policy, INT32& priority )
{
	int maxPriority = sched_get_priority_max(policy);
	int minPriority = sched_get_priority_min(policy);

	if (priority > maxPriority)
	{
		priority = maxPriority;
	}
	else if (priority < minPriority)
	{
		priority = minPriority;
	}

	return true;
}

bool WorkThread::setPolicy(int newPolicy)
{
	int policy;
	sched_param param;

	if( false == isRunning() )
		return false;

	pthread_getschedparam(thread, &policy, &param);
	if( policy != newPolicy )
	{
		int ret = pthread_setschedparam(thread, newPolicy, &param);
		if( ret != 0 ){
			printf("set %s policy %d error %d\n", className, newPolicy, ret);
		}
	}

	return true;
}

bool WorkThread::setPriority(INT32 newPriority)
{
	int policy;
	sched_param param;

	if( false == isRunning() )
		return false;

	pthread_getschedparam(thread, &policy, &param);

	validPriority( policy, newPriority );

	if(param.__sched_priority != newPriority)
	{
		param.sched_priority = newPriority;
		int ret = pthread_setschedparam(thread, policy, &param);
		if( 0 == ret )
			priority = newPriority;
		else
		{
			printf("set %s priority %d error %d\n", className, newPriority, ret);
		}
	}

	return true;
}

INT32 WorkThread::getPriority(void)
{
	if (priority == 0 && isRunning())
	{
		int policy;
		sched_param param;
		pthread_getschedparam(thread, &policy, &param);
		priority = param.sched_priority;
	}
	return priority;
}

void WorkThread::Suspend()
{
	if(!isRunning())
	{
		return;
	}
	AutoLock lock(apiMutex);
	suspend = true;
}

void WorkThread::resume()
{
	suspend = false;
}

bool WorkThread::isStopping(void) const
{
	return stopping;
}

bool WorkThread::isSuspend(void) const
{
	return suspend;
}
