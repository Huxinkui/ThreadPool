#include "ThreadManger.h"
#include "TaskNode.h"
#include "ThreadNode.h"

void  Run(void * arg, void * arg1)
{
	int num = *(int *)arg;
	ThreadManger * tmpMangerNode = (ThreadManger *) arg1;
	std::thread::id thread_id = std::this_thread::get_id();	
	std::unique_lock<std::mutex> lck(tmpMangerNode->mtx);

	cout << "This Thread Id :" << thread_id<< endl;		
	cout << " This is RUN    num: " << num << endl;
}

void Thread_cb(void * arg)
{

	ThreadManger * tmpMangerNode = (ThreadManger *) arg;
	if(tmpMangerNode != NULL)
	{
		while(1){
		//std::this_thread::sleep_for(std::chrono::seconds(1));
		std::thread::id thread_id = std::this_thread::get_id();
		
		//std::unique_lock<std::mutex> lck{tmpMangerNode->mtx};
		//tmpMangerNode->
		// {
		// 		std::unique_lock<std::mutex> lck(tmpMangerNode->mtx);
		// 		cout << "This Thread Id :" << thread_id<< endl;	
		// }
		//tmpMangerNode->	
		 //tmpMangerNode->
		{
		//std::unique_lock<std::mutex> lck(tmpMangerNode->mtx);
		while(tmpMangerNode->task_num == 0) 
			{	
				std::unique_lock<std::mutex> lck(tmpMangerNode->mtx);
				//std::thread::id thread_id = std::this_thread::get_id();	
				//cout << " This thread is wait() : " << thread_id<< endl;
				(tmpMangerNode->cv).wait(lck);
				lck.unlock();
			}
		}

		TaskNode * tmpTaskNode = tmpMangerNode->taskList_remove();

		if (tmpTaskNode != NULL)
		{
			//std::this_thread::sleep_for(std::chrono::seconds(1));
			
			//cout << "This func iter : " << tmpTaskNode->getfunc() << endl; ;
			//tmpMangerNode->
			(tmpTaskNode->getfunc())((void*)&(tmpTaskNode->taskId), arg);
			//tmpMangerNode->
			delete tmpTaskNode;
		}
		//tmpMangerNode->
		
	}
	}
}


ThreadManger::ThreadManger():counter(0),threadNode(NULL),taskNodeHead(NULL),taskNodeBack(NULL),task_num(0){
	// lck = std::unique_lock<std::mutex>(mtx);
	// 
}
ThreadManger::~ThreadManger(){}

//任务队列创建

int ThreadManger::taskList_create(int num)
{
	
	// 
	//task_num = num;
	for (int i = 0; i < num; ++i)
	{
		/* code */
		TaskNode * tmpNode = new TaskNode(i);
		tmpNode->setfunc(Run);
		tmpNode->taskId = i;
		int ret = taskList_add(tmpNode);
		//cout << " This is create task" << endl;
	}
	// 
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

	std::unique_lock<std::mutex> lck(mtx);
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
	cv.notify_all();
	
	return 0;
}

int ThreadManger::taskList_add1(TaskNode * taskNode){

	std::unique_lock<std::mutex> lck(mtx);
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
	cv.notify_all();
	
	return 0;
}
//链表尾部取节点
TaskNode* ThreadManger::taskList_remove(){

	std::unique_lock<std::mutex> lck(mtx);
	 
	TaskNode *  tmpNode = taskNodeBack;
	if (tmpNode != NULL){
		taskNodeBack->getperv()->setnext(NULL);

		taskNodeBack = tmpNode->getperv();
		task_num --;
		 
		return tmpNode;
		
	}
	//task_num --;
	 
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
		thread_id = (tmpThreadNode->Thread).get_id();
		//(tmpThreadNode->Thread).join();
		threadList_add(tmpThreadNode);
		counter++;
		
	}



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
	return 0;}

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


TaskNode * ThreadManger::getHeadNode(){
	return taskNodeHead;
}

















