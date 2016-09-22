#include <iostream>
#include "demo_common_lib.h"
#include <common_lib/Parameters.h>
#include <common_lib/UtiLite.h>

ThreadDemo::ThreadDemo(const ParametersMap & parameters)
{
    
}

ThreadDemo::~ThreadDemo()
{
}

void ThreadDemo::mainLoop()
{
    uSleep(1000);  
    UINFO("demo_common_lib loop\n");// print
}


void ThreadDemo::mainLoopKill()
{
}

int main()
{
	ULogger::setType(ULogger::kTypeConsole); //set 
	ULogger::setLevel(ULogger::kInfo);

	ParametersMap pamerater = Parameters::getDefaultParameters(); //parameters
	
	ThreadDemo *pThreadDemo = new ThreadDemo(pamerater);
	pThreadDemo->start();
	
	std::cout << Parameters::defaultMapStrategy()<<std::endl;
	while(1);
    return 0;
}
