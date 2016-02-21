/*
 * @brief: Condtion class
 * @author: luoxn28
 * @date: 2016.2.21
 */

#ifndef _SRC_CONDTION_H_
#define _SRC_CONDTION_H_

#include <pthread.h>
#include "Lock.h"

class CCondtion
{
public:
	CCondtion();
	~CCondtion();

	int Wait();
	bool WaitTime(unsigned long long wait_time);
	int Signal();
	int SignalAll();

private:
	CLock lock_;
	pthread_cond_t cond_;
};

#endif