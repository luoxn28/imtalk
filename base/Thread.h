/*
 * 线程封装类
 * @author: luoxn28
 * @create date: 2016.2.15
 */
#ifndef _BASE_THREAD_H_
#define _BASE_THREAD_H_

#include <pthread.h>

class IThread
{
public:
	IThread();
	virtual ~IThread();

	static void *StartRoutine(void *arg);

	virtual void StartThread();
	virtual void OnThreadRun(void) = 0;

protected:
	pthread_t thread_id_;
};

class IEventThread : public IThread
{
public:
	IEventThread();
	~IEventThread();

	virtual void OnThreadTick() = 0;
	virtual void OnThreadRun();
	virtual void StartThread();
	virtual void StopThread();
	bool IsRunning() { return running_; }

private:
	bool running_;
};

class CThreadNotify
{
public:
	CThreadNotify();
	~CThreadNotify();

	void Lock() { pthread_mutex_lock(&mutex_); }
	void Unlock() { pthread_mutex_lock(&mutex_); }
	void Wait() { pthread_cond_wait(&cond_, &mutex_); }
	void Signal() { pthread_cond_signal(&cond_); }

private:
	pthread_mutex_t mutex_;
	pthread_mutexattr_t mutexattr_;

	pthread_cond_t cond_;
};

#endif