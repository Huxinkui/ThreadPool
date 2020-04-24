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
	int taskList_add(TaskNode *);
	TaskNode* taskList_remove();
	int taskList_distory();


	//执行队列与销毁
	int tHredList_Create();
	int threadList_add(ThreadNode * );
	int tHreadList_Distory();

	ThreadNode * getThreadNode();
	std::mutex& getMtx();
	std::condition_variable& getCv();
	int getTaskNum();
	int setTaskMax();
	int getTaskMax();
	int setThreadMax();
	int getThreadMax();


private:
	
	int max_thread_num; // 最大线程数
	int counter ;//线程池中已有线程数
	int idle; //线程池中空闲线程数
	TaskNode * taskNodeHead;//头结点
	TaskNode * taskNodeBack;//尾结点
	ThreadNode * threadNode;//线程池
	std::mutex mtxadd;//最大任务互斥量
	std::mutex mtx;//取任务互斥量
	std::condition_variable cv;//信号量
	int task_num;// task工单量
	int task_max;// 任务队列最大容量



	
	
};







#endif