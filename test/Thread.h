 ///
 /// @file    Thread.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-06-08 09:59:03
 ///
 

#pragma once

#include "Noncopyable.h"
#include <pthread.h>
#include <functional>
#include <string>
using namespace std;

namespace wd
{

extern __thread int threadName;

class Thread 
: Noncopyable
{
public:
	using ThreadCallback = std::function<void()>;

	Thread(ThreadCallback && cb, int number)
	: _pthid(0)
	, _isRunning(false)
	, _cb(std::move(cb))
	, _number(number)
	{ }

	~Thread();

	void start();
	void join();

private:
	static void * threadFunc(void *);

private:
	pthread_t  _pthid;
	bool _isRunning;
	ThreadCallback _cb;
	int _number;
};

}//end of namespace wd
