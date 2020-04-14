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
	~ThreadNode();
	int setprev(ThreadNode *);
	ThreadNode* getprev();
	int setnext(ThreadNode *);
	ThreadNode* getnext();
	int setThread(std::thread &Thread)	;
	std::thread * getThread();

	int setThreadStatus( bool )	;
	bool getThreadStatus();


private:
	bool ThreadStatus;
	std::thread  Thread;
	ThreadNode * prev;
	ThreadNode * next;



	
};










#endif