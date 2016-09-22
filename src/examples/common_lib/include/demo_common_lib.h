#include <common_lib/UThread.h>
#include <common_lib/UEventsSender.h>
#include <common_lib/Parameters.h>



class  ThreadDemo :
	public UThread,  //inherit
	public UEventsSender
{
public:
	ThreadDemo(const ParametersMap & parameters = ParametersMap());
	virtual ~ThreadDemo();

private:
	virtual void mainLoop();
	virtual void mainLoopKill();
private:
	bool _mirroring;
	bool _colorOnly;
	int _imageDecimation;
};

