 ///
 /// @file    Thread.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-06-08 10:02:21
 ///
 
#include "Thread.h"

#include <stdio.h>
#include <errno.h>
#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

__thread int threadName;


using ThreadCallback = std::function<void()>;
struct ThreadData
{
    int _number;
	ThreadCallback _cb;

	ThreadData(int number, ThreadCallback cb)
	: _number(number)
	, _cb(cb)
	{}

	void runInThread()
	{
		//任务执行之前: do something
	    threadName = _number;	
		if(_cb)
			_cb();

		//任务执行之后: do something....
	}
};


Thread::~Thread()
{
	if(_isRunning) {
		pthread_detach(_pthid);	
		_isRunning = false;
	}
	cout << "~Thread()" << endl;
}

void Thread::start()
{
	ThreadData * data = new ThreadData(_number, _cb);

	if(pthread_create(&_pthid, nullptr, threadFunc, data)) {
		perror("pthread_create");
		return;
	}

	_isRunning = true;
}

void Thread::join()
{
	if(_isRunning) {
		pthread_join(_pthid, nullptr);
		_isRunning = false;
	}
}

void * Thread::threadFunc(void * arg)
{
	ThreadData * pdata = static_cast<ThreadData*>(arg);
	if(pdata)
		pdata->runInThread();
	
	delete pdata;

	return nullptr;
}

}//end of namespace wd
