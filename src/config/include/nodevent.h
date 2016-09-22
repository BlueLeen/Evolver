#ifndef CONFIGURE_NodEVENT_H_
#define CONFIGURE_NodEVENT_H_

#include "cfgevent.h"
#include <stdbool.h>

class NodEvent: public CfgEvent
{
public:
	virtual ~NodEvent(){};
	virtual void setUpdate(bool bUpdate) = 0;
	virtual bool getUpdate() = 0;
};

#endif
