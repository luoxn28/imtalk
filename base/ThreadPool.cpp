#include "ThreadPool.h"

#include <pthread.h>
#include <stdlib.h>

CWorkerThread::CWorkerThread()
{
	thread_id_ = -1;
	thread_idx_ = -1;
	task_cnt_ = 0;
}

CWorkerThread::~CWorkerThread()
{
	if (task_list_.empty()) {
		return;
	}

	std::list<ITask *>::iterator iter = task_list_.begin(), old_iter;
	while (iter != task_list_.end()) {
		old_iter = iter++;
		delete *old_iter;
	}
}

void *CWorkerThread::StartRoutine(void *arg)
{
	CWorkerThread *pthread = static_cast<CWorkerThread *> (arg);

	pthread->Execute();
	return NULL;
}

int CWorkerThread::Start()
{
	return pthread_create(&thread_id_, NULL, StartRoutine, this);
}

void CWorkerThread::Execute()
{
	while (true) {
		thread_notify_.Lock();

		/* Here must use while (...) */
		while (task_list_.empty()) {
			thread_notify_.Wait();
		}

		ITask *ptask = task_list_.front();
		task_list_.pop_front();
		thread_notify_.Unlock();

		ptask->run();
		delete ptask;
		task_cnt_++;
	}
}

void CWorkerThread::PushTask(ITask *ptask)
{
	thread_notify_.Lock();
	task_list_.push_back(ptask);
	thread_notify_.Signal();
	thread_notify_.Unlock();
}

////////////
CThreadPool::CThreadPool()
{
	worker_size_ = 0;
}

CThreadPool::~CThreadPool()
{
}

int CThreadPool::Init(int worker_size)
{
	worker_size_ = worker_size;
	worker_vector_.resize(worker_size_);
	
	for (int i = 0; i < worker_size_; i++) {
		worker_vector_[i].SetThreadIdx(i);
		worker_vector_[i].Start();
	}

	return 0;
}

void CThreadPool::AddTask(ITask *ptask)
{
	int thread_idx = random() % worker_size_;
	worker_vector_[thread_idx].PushTask(ptask);
}