#include "ThreadManger.h"
#include "TaskNode.h"
#include "ThreadNode.h"

void  Run(void * arg, void * arg1)
{
	int num = *(int *)arg;
	ThreadManger * tmpMangerNode = (ThreadManger *) arg1;
	std::thread::id thread_id = std::this_thread::get_id();	
	std::unique_lock<std::mutex> lck(tmpMangerNode->getMtx());
	cout << "This Thread Id :" << thread_id ;		
	cout << "  This is RUN    num: " << num << endl;
}

void Thread_cb(void * arg)
{

	ThreadManger * tmpMangerNode = (ThreadManger *) arg;
	if(tmpMangerNode != NULL)
	{
		while(1){
		
			std::unique_lock<std::mutex> lck(tmpMangerNode->getMtx(), std::defer_lock);
			lck.lock();
			while(tmpMangerNode->getTaskNum() == 0) 
					(tmpMangerNode->getCv()).wait(lck);
			lck.unlock();
			
			TaskNode * tmpTaskNode = tmpMangerNode->taskList_remove();
			
			if (tmpTaskNode != NULL)
			{
				
				(tmpTaskNode->getfunc())((void*)&(tmpTaskNode->taskId), arg);
				
				delete tmpTaskNode;
			}
			
		}
	}
}


ThreadManger::ThreadManger():counter(0),threadNode(NULL),taskNodeHead(NULL),taskNodeBack(NULL),task_num(0){

}
ThreadManger::~ThreadManger(){}

//任务队列创建

int ThreadManger::taskList_create(int num)
{
	
	for (int i = 0; i < num; ++i)
	{
		/* code */
		TaskNode * tmpNode = new TaskNode(i);
		tmpNode->setfunc(Run);
		tmpNode->taskId = i;
		int ret = taskList_add(tmpNode);
	}
	// 
	return 0;
}
//双向链表头部加节点
int ThreadManger::taskList_add(TaskNode * taskNode){

	//std::this_thread::sleep_for(std::chrono::seconds(1));
	//
	//
	//
	std::unique_lock<std::mutex> lckadd(mtxadd, std::defer_lock);
	lckadd.lock();
	while( task_max == task_num) 
	{
		cout << "THE TaskList is FULL" << endl;
		cvadd.wait(lckadd);
	}
	lckadd.unlock();
		
	std::unique_lock<std::mutex> lck(mtx,std::defer_lock);
	lck.lock();
		
	// lckadd.unlock();
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
	task_num++;
	cv.notify_one();
	lck.unlock();
	return 0;
}


//链表尾部取节点
TaskNode* ThreadManger::taskList_remove(){

	std::unique_lock<std::mutex> lck(mtx,std::defer_lock);
	lck.lock();
	 
	TaskNode *  tmpNode = taskNodeBack;
	if (tmpNode != NULL){
		if(taskNodeBack->getperv() == NULL)
		{
			taskNodeHead = NULL;
			taskNodeBack = NULL;
		}
		else
		{
			taskNodeBack->getperv()->setnext(NULL);
			taskNodeBack = tmpNode->getperv();
		}
		task_num --;
		cvadd.notify_all();
		lck.unlock();
		return tmpNode;
		
	}
	 lck.unlock();
	return NULL;
}





	//线程队列创建
int ThreadManger::tHredList_Create(int num){ 
	
	max_thread_num = num;	
	while(counter < max_thread_num)
	{

		ThreadNode * tmpThreadNode = new ThreadNode();

		tmpThreadNode->Thread = std::thread(Thread_cb,this);
		tmpThreadNode->thread_id = (tmpThreadNode->Thread).get_id();
		threadList_add(tmpThreadNode);
		counter++;
		
	}



	return 0;
}

//双向链表头部加节点
int ThreadManger::threadList_add(ThreadNode * threadNode){

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
	return 0;
}

ThreadNode * ThreadManger::getThreadNode(){
	return threadNode;
}
std::mutex& ThreadManger::getMtx(){ //互斥量在作为私有成员时，get获取需要传引用
	return mtx;
}
std::condition_variable& ThreadManger::getCv(){//条件变量在作为私有成员时，get获取需要传引用
	return cv;
}

int ThreadManger::getTaskNum(){
	return task_num;
}

int ThreadManger::setTaskMax(){
	cout << "请输入最大任务队列 ： " ;
	cin >> task_max;
	return 0;
}

int ThreadManger::getTaskMax(){
	return task_max;
}















