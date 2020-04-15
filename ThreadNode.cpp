#include"ThreadNode.h"



ThreadNode::ThreadNode():ThreadStatus(false),prev(NULL),next(NULL){

}
ThreadNode::~ThreadNode(){

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








int ThreadNode::setThreadStatus(bool ThreadStatus)
{
	ThreadStatus = ThreadStatus;
	return 1;
}


bool ThreadNode::getThreadStatus()
{
	return ThreadStatus;
}

// std::thread * ThreadNode::getThread()
// {
	
// 	return &Thread;
// }
// int ThreadNode::setThread(std::thread &Thread)
// {
// 	Thread = std::thread(std::move(Thread));
// 	return 1;
// }