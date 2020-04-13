#include"ThreadNode.h"
#include "TaskNode.h"

void * thread_cb(TaskNode *task,std::chrono::seconds *sleep_time, int *test_id)
{

	//std::thread::id test_id = std::this_thread::get_id();
	cout << "This Thread id is :" << *test_id << endl ;
	std::this_thread::sleep_for(*sleep_time);

	if(task == NULL)
	{
		cout<< "task is NULL" << endl;
		return NULL;
	}
	(*(task->getfunc()))(NULL);
	cout << " This task return " << std::endl;
	return NULL;
}

ThreadNode::ThreadNode():thread_id(0),prev(NULL),next(NULL){

}
ThreadNode::~ThreadNode(){

}

ThreadNode::ThreadNode(const ThreadNode &node)
{
	this->thread_id = node.thread_id;
	this->prev = node.prev;
	this->next = node.next;
}




int ThreadNode::setprev(ThreadNode * node){
	if(node != NULL)
	{
		prev = node; return 1;
	}else{
		return -2;
	}
	
}

ThreadNode* ThreadNode::getprev()
{
	return prev;
}


int ThreadNode::setnext(ThreadNode * node){
	if(node != NULL)
	{
		next = node; return 1;
	}else{
		return -2;
	}
}

ThreadNode* ThreadNode::getnext(){
	return next;
}


int ThreadNode::setThreadId(std::thread::id id)
{
	this->thread_id = id;
	return 1;
}



std::thread::id ThreadNode::getThreadId()
{
	return thread_id;
}




int ThreadNode::setTaskNode(TaskNode * node)
{
	taskNode = node;
	return 0;
}




int ThreadNode::initThread()
{

	th =  std::thread(thread_cb, taskNode, &sleep_time,  &test_id);
	th.join();
	//std::this_thread::sleep_for(std::chrono::seconds(1));
	return 0;
}




int ThreadNode::Print()
{
	std::cout << "This thread_id " << thread_id << std::endl;
	return 1;
}