/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	AutoLock.cpp
 * File Path:
 * Author:		Richard
 * Version:		1.0
 * Description:
 *
 * History:
 *  Date		Author			CR number	CR Title
 */

#include "AutoLock.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <algorithm>
#include <errno.h>
#include <pthread.h>
#include <fcntl.h>
#include <assert.h>
#include <string.h>
#include<unistd.h>

using namespace std;

constexpr INT32U RW_RIGHT = 0666;

MutexHeavyLock::MutexHeavyLock(const char* name)
{
	mutexLock = nullptr;
	if (nullptr != name)
	{
		strncpy(nameMember, name, std::min(sizeof(nameMember), strlen(name)));
		//	cross processes
		mutexLock = getSharedMutex(name);
	}
	else
	{
		assert(false);
	}
}

MutexHeavyLock::~MutexHeavyLock()
{
	if( mutexLock )
		detatchFromSharedMem(mutexLock, nameMember);
}

pthread_mutex_t* MutexHeavyLock::getSharedMutex(const char* pathName)
{
	bool needInit = false;
	pthread_mutex_t* pMutex = nullptr;
	INT32 fd = open(pathName, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
	if (-1 != fd)
	{
		needInit = true;
	}
	else
	{
		assert(errno == EEXIST);
		if (errno != EEXIST)
		{
			close(fd);
			return nullptr;
		}
	}

	key_t shmkey = ftok(pathName, 0);
	if (-1 != shmkey)
	{
		int shmid = shmget(shmkey, sizeof(pthread_mutex_t), RW_RIGHT | IPC_CREAT);
		if (-1 != shmid)
		{
			pMutex = (pthread_mutex_t*)shmat(shmid, nullptr, 0);
			if (needInit)
			{
				sharedMutexInit(pMutex);
			}
		}
	}

	close(fd);

	return pMutex;
}

pthread_mutex_t* MutexHeavyLock::sharedMutexInit(pthread_mutex_t* pMutex)
{
	if (nullptr != pMutex)
	{
		pthread_mutexattr_t mattr;
		pthread_mutexattr_init(&mattr);
		pthread_mutexattr_setrobust_np(&mattr, PTHREAD_MUTEX_ROBUST_NP);
		pthread_mutexattr_setpshared(&mattr, PTHREAD_PROCESS_SHARED);
		pthread_mutexattr_settype(&mattr, PTHREAD_MUTEX_RECURSIVE);
		pthread_mutex_init(pMutex, &mattr);
		pthread_mutexattr_destroy(&mattr);
	}
	return pMutex;
}

int MutexHeavyLock::detatchFromSharedMem(pthread_mutex_t* pMutex, const char* pathName)
{

	key_t shmkey = ftok(pathName, 0);
	bool deleteFile = false;
	INT32 shmid = shmget(shmkey, sizeof(pthread_mutex_t), RW_RIGHT | IPC_CREAT);
	if (-1 != shmid)
	{
		shmid_ds ds;
		if (0 == shmctl(shmid, IPC_STAT, &ds))
		{
			if (1 == ds.shm_nattch)
			{
				pthread_mutex_destroy(pMutex);
				deleteFile = true;
			}
		}
		if (0 == shmdt(pMutex))
		{
			if (deleteFile)
			{
				if (0 == shmctl(shmid, IPC_RMID, nullptr) )
				{
					return remove(pathName);
				}
			}
			else
			{
				return 0;
			}
		}
	}
	return -1;
}

AutoLock::AutoLock(MutexLock& lock)
	: mutexLock(lock)
{
	mutexLock.lock();
}

AutoLock::~AutoLock()
{
	mutexLock.unlock();
}

MicroportMutex::MicroportMutex(pthread_mutex_t *mutexT)
{
	mutexObj = mutexT;
	pthread_mutex_lock( mutexObj );
}

MicroportMutex::~MicroportMutex()
{
	pthread_mutex_unlock( mutexObj );
}
