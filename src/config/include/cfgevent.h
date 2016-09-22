#ifndef CONFIGURE_CFGEVENT_H_
#define CONFIGURE_CFGEVENT_H_

class CfgEvent
{
public:
	virtual ~CfgEvent(){};
	virtual void enroll() = 0;
	virtual void notify() = 0;
};

#endif
