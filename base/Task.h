/*
 * @brief: task info
 * @author: luoxn28
 * @date: 2016.2.17
 */
#ifndef _SRC_TASK_H_
#define _SRC_TASK_H_

class ITask
{
public:
	ITask() {}
	virtual ~ITask() {}

	virtual void run() = 0;
};

#endif /* #define _SRC_TASK_H_ */