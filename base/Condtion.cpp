/*
 * @brief: Condtion class
 * @author: luoxn28
 * @date: 2016.2.21
 */

#include "Condtion.h"
#include <errno.h>

CCondtion::CCondtion()
{
	pthread_cond_init(&cond_, NULL);
}

CCondtion::~CCondtion()
{
	pthread_cond_destroy(&cond_);
}

int CCondtion::Wait()
{
	lock_.Lock();
	return pthread_cond_wait(&cond_, &lock_.GetMutex());
	lock_.Unlock();
}

bool CCondtion::WaitTime(unsigned long long wait_time)
{
	unsigned long long ntime = wait_time * 1000000;
	struct timespec stime;
	unsigned long long nsec = ntime / 1000000;
	unsigned long long nmicrosec = ntime % 1000000;
	stime.tv_sec = nsec;
	stime.tv_nsec = nmicrosec;
	lock_.Lock();
	if (ETIMEDOUT == pthread_cond_timedwait(&cond_, &lock_.GetMutex(), &stime)) {
		lock_.Unlock();
		return false;
	}
	lock_.Unlock();

	return true;
}

int CCondtion::Signal()
{
	return pthread_cond_signal(&cond_);
}

int CCondtion::SignalAll()
{
	return pthread_cond_broadcast(&cond_);
}

