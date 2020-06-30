
#ifndef TASK_NODE_H
#define TASK_NODE_H
#include<iostream>
using std::cout;
using std::endl;
typedef void (*FUN)(void *,void *);
//任务队列

class TaskNode
{
public:
	TaskNode();
	TaskNode(int);

	TaskNode(int, FUN);
	TaskNode(const TaskNode &);
	TaskNode &operator=(const TaskNode & tp);

	~TaskNode();
	int setfunc(FUN fun);
	FUN getfunc();

	int setperv(TaskNode *);
	TaskNode* getperv();

	int setnext(TaskNode *);
	TaskNode* getnext();

	int remove();

	void Print();

	
	int taskId;

private:

FUN fun;
TaskNode * perv;
TaskNode * next;


	
};






#endif

