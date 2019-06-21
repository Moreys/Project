 ///
 /// @file    TestThread.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-06-08 10:19:45
 ///
 
#include "Thread.h"

#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <memory>
using namespace std;


class MyTask 
{
public:
	~MyTask() {	cout << "~MyTask()" << endl;}

	void process() 
	{
		::srand(::clock());
		int cnt = 10;
		while(cnt--) {
			int number = ::rand() % 100;
			//cout << "sub thread " << pthread_self() 
			cout << wd::threadName  
				 << ": get a number = " << number << endl;

			::sleep(1);
		}
	}
};
             
//json格式
 
int main(void)
{

	cout << wd::threadName << endl; 

	MyTask task;

	//如果是以指针的方式传递对象，要保证在执行process方法时，
	//该对象生命周期没有结束；如果结束，执行会出错
	//
	//绑定对象时，也可以以值传递方式传递对象
	unique_ptr<wd::Thread> mythread(
		new wd::Thread(
			//std::bind(&MyTask::process, task), "thread 1"));
			std::bind(&MyTask::process, task),9));
	mythread->start();
	mythread->join();
	cout << ">>> " << wd::threadName << endl; 

	return 0;
}
