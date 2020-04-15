#include <iostream>
#include "ThreadManger.h"

using namespace std;

int main(void)
{

	

	ThreadManger  tm;
	tm.taskList_create(5);
	tm.tHredList_Create(2);
	
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



