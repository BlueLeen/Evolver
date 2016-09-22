#ifndef CONFIGURE_COMMUCFG_H_
#define CONFIGURE_COMMUCFG_H_

#include <ros/ros.h>
#include "nodevent.h"
#include "common.h"

class CommuCfg : public NodEvent
{
public:
	CommuCfg();
	virtual ~CommuCfg();
	void enroll();
	void notify();
	void setUpdate(bool bUpdate);
	bool getUpdate();
public:
	static const NodeFlag nodeflag = COMM;
private:
	bool m_bUpdate;
	ros::Publisher m_pubFlush;
};

#endif
