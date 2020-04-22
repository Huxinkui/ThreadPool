#ifndef THREAD_MANGER_H
#define THREAD_MANGER_H


#include <iostream>
#include <mutex>              
#include <condition_variable>
#include "TaskNode.h"
#include "ThreadNode.h"
using namespace std;




class ThreadManger
{
public:
	ThreadManger();
	~ThreadManger();

	//任务队列

	int taskList_create(int);
	int taskList_distory();
	int taskList_add(TaskNode *);
	int taskList_add1(TaskNode *);
	TaskNode* taskList_remove();


	//执行队列与销毁
	int tHredList_Create(int i);
	int tHreadList_Distory();
	int threadList_add(ThreadNode * );

	TaskNode * getHeadNode();
	std::thread::id thread_id;
	ThreadNode * threadNode;
	TaskNode * taskNodeBack;

	std::mutex mtx;//互斥量
	std::condition_variable cv;//信号量
	
	int task_num;// task工单量

private:
	
	int max_thread_num; // 最大线程数
	int counter ;//线程池中已有线程数
	int idle; //线程池中空闲线程数
	TaskNode * taskNodeHead;

	
	
};







#endif