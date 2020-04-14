#include "ThreadManger.h"

#include "TaskNode.h"
#include "ThreadNode.h"

void  Run(void * i)
{
	int num = *(int *)i;
	cout << "num: " << num << endl;
	//return 0;
}


ThreadManger::ThreadManger():counter(0),threadNode(NULL),taskNodeHead(NULL),taskNodeBack(NULL),task_num(0){}
ThreadManger::~ThreadManger(){}

//任务队列创建

int ThreadManger::taskList_create(int num)
{
	mtx.lock();
	task_num = num;

	for (int i = 0; i < num; ++i)
	{
		/* code */
		TaskNode * tmpNode = new TaskNode(i);
		tmpNode->setfunc(Run);
		int ret = taskList_add(tmpNode);
	}
	mtx.unlock();
	return 0;
}

//销毁双向链表
int ThreadManger::taskList_distory(){

	while(taskNodeBack != NULL)
	{
		if(taskNodeBack->getperv() != NULL)
		{
			taskNodeBack->Print();
			TaskNode * tmpNode = taskNodeBack->getperv();
			delete taskNodeBack;
			taskNodeBack = tmpNode;
		}
		else
		{
			taskNodeBack->Print();
			delete taskNodeBack;
			taskNodeBack = NULL;
		}
	}
	return 0;
}
//双向链表头部加节点
int ThreadManger::taskList_add(TaskNode * taskNode){
	//std::cout << "This is Test1" <<std::endl;

	taskNode->Print();
	mtx.lock();
	if(this->taskNodeHead == NULL && this->taskNodeBack == NULL)
	{
		this->taskNodeHead = taskNode;
		this->taskNodeBack = taskNode;
	}
	else{

		this->taskNodeHead->setperv(taskNode);
		taskNode->setnext(this->taskNodeHead);
		this->taskNodeHead = taskNode;		

	}
	mtx.unlock();
	return 0;
}
//链表尾部取节点
TaskNode* ThreadManger::taskList_remove(){

	mtx.lock();
	TaskNode *  tmpNode = taskNodeBack;
	if (tmpNode != NULL){
		taskNodeBack->getperv()->setnext(NULL);

		taskNodeBack = tmpNode->getperv();
		task_num --;
		return tmpNode;
		mtx.unlock();
	}
	mtx.unlock();
	return NULL;
}





	//线程队列创建
int ThreadManger::tHredList_Create(int num){ 

	max_thread_num = num;
	//mtx.lock();
	
	while(counter < max_thread_num)
	{

		ThreadNode * tmpThreadNode = new ThreadNode();
		threadList_add(tmpThreadNode);
		counter++;
		
	}

	//mtx.unlock();



	return 0;
}

int ThreadManger::tHreadList_Distory(){ 

while(threadNode != NULL)
	{
		
		if(threadNode->getnext() != NULL)
		{
			ThreadNode * tmpNode = threadNode->getnext();
			delete threadNode;
			threadNode = tmpNode;
		}
		else
		{
			delete threadNode;
			threadNode = NULL;
		}
	}
	return 0;
}

//双向链表头部加节点
int ThreadManger::threadList_add(ThreadNode * threadNode){
	//std::cout << "This is Test1" <<std::endl;

	mtx.lock();

	if(this->threadNode == NULL)
	{
		//threadNode -> Print();
		this->threadNode = threadNode;
	}
	else{
		//threadNode -> Print();
		this->threadNode->setprev(threadNode);
		threadNode->setnext(this->threadNode);
		this->threadNode = threadNode;		

	}
	mtx.unlock();
	return 0;
}


















