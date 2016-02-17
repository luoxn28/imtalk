/*
 * @brief: thread pool
 * @author: luoxn28
 * @date: 2016.2.17
 */

#ifndef _SRC_THREADPOOL_H_
#define _SRC_THREADPOOL_H_

#include <list>
#include <vector>
#include "Task.h"
#include "Thread.h"

class CWorkerThread
{
public:
	CWorkerThread();
	~CWorkerThread();

	static void *StartRoutine(void *arg);

	int Start();
	virtual void Execute();
	void PushTask(ITask *ptask);

	void SetThreadIdx(int idx) { thread_id_ = idx; }

private:
	pthread_t thread_id_;
	int thread_idx_;
	int task_cnt_;
	CThreadNotify thread_notify_;
	std::list<ITask *> task_list_;
};

class CThreadPool
{
public:
	CThreadPool();
	virtual ~CThreadPool();

	int Init(int worker_size);
	void Destroy() {
		worker_vector_.clear();
		worker_size_ = 0;
	}

	void AddTask(ITask *ptask);

	int GetThreadNums() {
		return worker_size_;
	}

private:
	int worker_size_;
	std::vector<CWorkerThread> worker_vector_;
};

#endif /* #define _SRC_THREADPOOL_H_ */