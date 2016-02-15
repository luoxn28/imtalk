/*
* 线程封装类
* @author: luoxn28
* @create date: 2016.2.15
*/

#include "Thread.h"

IThread::IThread() : thread_id_(0) {}

IThread::~IThread() {}

void *IThread::StartRoutine(void *arg)
{
	IThread *pthread = static_cast<IThread *>(arg);
	pthread->OnThreadRun();
	return NULL;
}

void IThread::StartThread()
{
	pthread_create(&thread_id_, NULL, StartRoutine, this);
}


IEventThread::IEventThread()
{
	running_ = false;
}

IEventThread::~IEventThread()
{
	running_ = false;
	StopThread();
}

void IEventThread::OnThreadRun()
{
	while (running_) {
		OnThreadTick();
	}
}

void IEventThread::StartThread()
{
	running_ = true;
	IThread::StartThread();
}

void IEventThread::StopThread()
{
	running_ = false;
}


CThreadNotify::CThreadNotify()
{
	pthread_mutexattr_init(&mutexattr_);
	pthread_mutexattr_settype(&mutexattr_, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&mutex_, &mutexattr_);

	pthread_cond_init(&cond_, NULL);
}

CThreadNotify::~CThreadNotify()
{
	pthread_mutexattr_destroy(&mutexattr_);
	pthread_mutex_destroy(&mutex_);
	pthread_cond_destroy(&cond_);
}
