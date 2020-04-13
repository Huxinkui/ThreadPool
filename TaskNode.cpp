
#include "TaskNode.h"


TaskNode::TaskNode():taskId(0),perv(NULL),next(NULL)
{

}

TaskNode::TaskNode(int i): taskId(i),perv(NULL),next(NULL)
{

}

TaskNode::TaskNode(int i, FUN fun):fun(fun), taskId(i),perv(NULL),next(NULL)
{

}

TaskNode::TaskNode(const TaskNode &node)
{
	this->taskId = node.taskId;
	this->perv = node.perv;
	this->next = node.next;
	this->fun = node.fun;
}

TaskNode &TaskNode::operator=(const TaskNode &tmpNode)
{
	if(this != &tmpNode)
	{
		this->taskId = tmpNode.taskId;
		this->perv = tmpNode.perv;
		this->next = tmpNode.next;
		this->fun = tmpNode.fun;
	}
	return (*this);
}


TaskNode::~TaskNode()
{

}

int TaskNode::setfunc(FUN fun)
{
	if(fun != NULL)
	{
		this->fun = fun;
		return 1;
	}
	else
		return 0;


}
FUN TaskNode::getfunc()
{
	return fun;
	
}

int TaskNode::setperv(TaskNode * perv)
{
	if(perv != NULL)
	{
		this->perv = perv;
		return 1;
	}
	else
		return -1;

}
TaskNode* TaskNode::getperv()
{
	if(perv != NULL)
	{
		return perv;
	}
	else
		return NULL;
}


int TaskNode::setnext(TaskNode * next)
{
	if(next != NULL)
	{
		this->next = next;
		return 1;
	}
	else
		return -1;

}
TaskNode* TaskNode::getnext()
{
	if(next != NULL)
	{
		return next;
	}
	else
		return NULL;
}

void TaskNode::Print()
{
	cout << "Task Id ： " << taskId << endl;
}

