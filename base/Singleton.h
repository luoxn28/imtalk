/*
 * @brief: singleton mode
 * @author: luoxn28
 * @date: 2016.2.20
 */

#ifndef _BASE_SINGLETON_H_
#define _BASE_SINGLETON_H_

#include <iostream>

/*
 * @note: This is not safe in threads
 */
template <typename T>
class Singleton
{
public:
	static T *GetInstance() {
		if (!instance_) {
			instance_ = new T;
		}
		return instance_;
	}

	static void Destroy() {
		delete instance_;
		instance_ = NULL;
	}

protected:
	Singleton() {
		instance_ = static_cast<T *>(this);
	}
	~Singleton() {
		instance_ = NULL;
	}

private:
	// Not implement
	Singleton(Singleton &) {}
	Singleton &operator=(Singleton &) { return *this; }

	static T *instance_;
};

template <typename T>
T* Singleton<T>::instance_ = NULL;

#endif

/*
// Test for Singleton
#include <iostream>
#include "Singleton.h"

using namespace std;

class Node : public Singleton<Node>
{
	friend class Singleton<Node>;
public:
	void func() {
		cout << "Node::func()" << endl;
	}
};

int main()
{
	Node *node = Node::GetInstance();

	node->func();

	return 0;
}
*/