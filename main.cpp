#include <iostream>
#include "ThreadManger.h"

using namespace std;

void  run_func(void * arg, void * arg1)
{
	int num = *(int *)arg;
	ThreadManger * tmpMangerNode = (ThreadManger *) arg1;
	std::unique_lock<std::mutex> lck(tmpMangerNode->mtx);
	cout << " This is run_func    num: " << num << endl;

}

int main(void)
{

	ThreadManger  tm;
	tm.tHredList_Create(2);
	tm.taskList_create(100);

	for(int i = 10; i < 20; i++)
	{
		
		std::this_thread::sleep_for(std::chrono::seconds(3));
		cout << " This is create task" << endl;
		TaskNode * tmpNode = new TaskNode(i);
		tmpNode->setfunc(run_func);
		tmpNode->taskId = i;
		int ret = tm.taskList_add1(tmpNode);
	}

	
	for(auto tmpiter = tm.threadNode; tmpiter != NULL;tmpiter = tm.threadNode->getnext())
	{
		tmpiter->Thread.join();
	}


	



	// tm.taskList_create(5);

	// cout << " This is distory  " << endl;
	// //tm.taskList_distory();

	// for (int i = 0 ; i < 5 ; i++) {
	// 		TaskNode * tmpNode = tm.taskList_remove();
	// 		 tmpNode->Print() ;
	// 		 delete tmpNode;
	// 		 tmpNode = NULL; 

	// }
	// 
	// tm.tHredList_Create(5);
	
	// tm.tHreadList_Distory();

	return 0;
}



