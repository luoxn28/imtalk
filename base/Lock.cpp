/*
 * »¥³âËø(°üÀ¨¶ÁÐ´Ëø)·â×°Àà
 * @author: luoxn28
 * @create date: 2016.2.16
 */

#include "Lock.h"

CLock::CLock()
{
	pthread_mutex_init(&mutex_, NULL);
}

CLock::~CLock()
{
	pthread_mutex_destroy(&mutex_);
}

int CLock::Lock()
{
	return pthread_mutex_lock(&mutex_);
}

int CLock::Unlock()
{
	return pthread_mutex_unlock(&mutex_);
}

int CLock::TryLock()
{
	return pthread_mutex_trylock(&mutex_);
}


CAutoLock::CAutoLock(CLock *plcok)
{
	plock_ = plcok;
	if (plock_) {
		plock_->Lock();
	}
}

CAutoLock::~CAutoLock()
{
	if (plock_) {
		plock_->Unlock();
	}
}


CRWLock::CRWLock()
{
	pthread_rwlock_init(&rwlock_, NULL);
}

CRWLock::~CRWLock()
{
	pthread_rwlock_destroy(&rwlock_);
}

int CRWLock::Rlock()
{
	return pthread_rwlock_rdlock(&rwlock_);
}

int CRWLock::Wlock()
{
	return pthread_rwlock_wrlock(&rwlock_);
}

int CRWLock::Unlock()
{
	return pthread_rwlock_unlock(&rwlock_);
}

int CRWLock::TryRlock()
{
	return pthread_rwlock_tryrdlock(&rwlock_);
}

int CRWLock::TryWlock()
{
	return pthread_rwlock_trywrlock(&rwlock_);
}


CAutoRWLock::CAutoRWLock(CRWLock *prwlock, bool is_rlock)
{
	prwlock_ = prwlock;
	if (prwlock_) {
		if (is_rlock) {
			prwlock_->Rlock();
		}
		else {
			prwlock_->Wlock();
		}
	}
}

CAutoRWLock::~CAutoRWLock()
{
	if (prwlock_) {
		prwlock_->Unlock();
	}
}