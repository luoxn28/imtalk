/*
 * »¥³âËø(°üÀ¨¶ÁÐ´Ëø)·â×°Àà
 * @author: luoxn28
 * @create date: 2016.2.16
 */

#ifndef _BASE_LOCK_H_
#define _BASE_LOCK_H_

#include <pthread.h>

class CLock
{
public:
	CLock();
	virtual ~CLock();

	int Lock();
	int Unlock();
	int TryLock();

private:
	pthread_mutex_t mutex_;
};

class CAutoLock
{
public:
	CAutoLock(CLock *plock);
	virtual ~CAutoLock();

private:
	CLock *plock_;
};

// ¶ÁÐ´Ëø
class CRWLock
{
public:
	CRWLock();
	virtual ~CRWLock();

	int Rlock();
	int Wlock();
	int Unlock();
	int TryRlock();
	int TryWlock();

private:
	pthread_rwlock_t rwlock_;
};

#endif