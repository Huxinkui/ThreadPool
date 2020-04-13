#ifndef THREAD_NODE_H
#define THREAD_NODE_H
#include <iostream>
#include <thread>
#include <chrono>
#include "TaskNode.h"
using std::thread;

class ThreadNode
{
public:
	ThreadNode();
	ThreadNode(const ThreadNode &node);
	~ThreadNode();
	int setprev(ThreadNode *);
	ThreadNode* getprev();
	int setnext(ThreadNode *);
	ThreadNode* getnext();
	int setThreadId(std::thread::id );
	std::thread::id  getThreadId();
	int initThread();

	int setTaskNode(TaskNode *);
	

	int runThread();

	int Print();

	int test_id ;
	std::chrono::seconds sleep_time;

private:

	std::thread::id  thread_id;
	ThreadNode * prev;
	ThreadNode * next;
	TaskNode * taskNode;
	std::thread  th;



	
};










#endif