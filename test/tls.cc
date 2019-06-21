 ///
 /// @file    tls.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-06-15 09:36:43
 ///
 
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <iostream>
using namespace std;

//errno就是一个线程局部存储(TLS)

int globalNumber = 10;//全局变量
//__thread变量是某一个线程内部定义的
//只要创建一个线程，__thread变量在各自的线程栈空间中会创建一个独立的副本
__thread int threadNumber = 0;


void * threadfunc1(void * arg)
{
	printf(">> thread 1 errno's address %p\n", &errno);
	threadNumber = 1;
	printf(">> thread 1 threadNumber = %d\n", threadNumber);
	printf(">> thread 1 &threadNumber = %p\n", &threadNumber);

	return nullptr;
}
             
void * threadfunc2(void * arg)
{
	printf(">> thread 2 errno's address %p\n", &errno);
	threadNumber = 2;
	printf(">> thread 2 threadNumber = %d\n", threadNumber);
	printf(">> thread 2 &threadNumber = %p\n", &threadNumber);

	return nullptr;
}
 
int main(void)
{
	threadNumber = 100;
	printf(">> main thread errno's address %p\n", &errno);
	printf(">> main thread threadNumber = %d\n", threadNumber);
	printf(">> main thread &threadNumber = %p\n", &threadNumber);
	pthread_t pthid1, pthid2;
	pthread_create(&pthid1, nullptr, threadfunc1, nullptr);
	pthread_create(&pthid2, nullptr, threadfunc2, nullptr);

	pthread_join(pthid1, nullptr);
	pthread_join(pthid2, nullptr);

	return 0;
}
