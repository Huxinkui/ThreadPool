#include <iostream>
#include "ThreadManger.h"

using namespace std;

int main(void)
{

	

	ThreadManger  tm;
	tm.tHredList_Create(2);

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



