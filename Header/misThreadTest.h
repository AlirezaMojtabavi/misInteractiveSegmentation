#pragma once


#include <windows.h>
#include <process.h>    /* _beginthread, _endthread */
#include <stddef.h>
#include <stdlib.h>
#include <conio.h>


#include "itkConditionVariable.h"
#include "itkMutexLock.h"
//#include <boost/thread/thread.h>
#include  <iostream>
#include "vtkTimerLog.h"

class misThreadTest
{
public:


	static void RunMainFunctionInThread(int priority = THREAD_PRIORITY_NORMAL,bool waitTillEnd = false,int threadNumber =0);
	static void RunMainFunctionPackInThread(int threadNumbers);
	static void RunMainFunction(void *param =0);

	misThreadTest(void);
	~misThreadTest(void);
};
