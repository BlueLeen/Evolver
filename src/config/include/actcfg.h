/*
 * actcfg.h
 *
 *  Created on: Sep 18, 2016
 *      Author: su
 */

#ifndef CONFIGURE_ACTCFG_H_
#define CONFIGURE_ACTCFG_H_

#include <ros/ros.h>
#include "nodevent.h"
#include "common.h"

class ActCfg : public NodEvent {
public:
	ActCfg();
	virtual ~ActCfg();
	void enroll();
	void notify();
	void setUpdate(bool bUpdate);
	bool getUpdate();
public:
	static const NodeFlag nodeflag = ACTION;
private:
	bool m_bUpdate;
	ros::Publisher m_pubFlush;
};

#endif /* ACTCFG_H_ */
