#include <iostream>
#include "ThreadManger.h"



using namespace std;

void  run_func(void * arg, void * arg1) //任务节点函数2
{
	int num = *(int *)arg;
	ThreadManger * tmpMangerNode = (ThreadManger *) arg1;
	std::unique_lock<std::mutex> lck(tmpMangerNode->getMtx());

	std::thread::id thread_id = std::this_thread::get_id();	
	cout << "This Thread Id :" << thread_id ;
	cout << " This is run_func    num: " << num+1 << endl;

}

int main(void)
{


	ThreadManger  tm;
	tm.setTaskMax();
	tm.setThreadMax();
	tm.tHredList_Create();
	tm.taskList_create(100);//使用Run作为任务队列中的任务创建任务队列

		
		for(auto tmpiter = tm.getThreadNode(); tmpiter != NULL;tmpiter = (tm.getThreadNode())->getnext())
		{
			tmpiter->Thread.join();
		}


	return 0;
}



