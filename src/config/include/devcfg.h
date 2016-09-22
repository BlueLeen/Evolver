/*
 * devcfg.h
 *
 *  Created on: Sep 18, 2016
 *      Author: su
 */

#ifndef CONFIGURE_DEVCFG_H_
#define CONFIGURE_DEVCFG_H_

#include <ros/ros.h>
#include "nodevent.h"
#include "common.h"

class DevCfg : public NodEvent {
public:
	DevCfg();
	virtual ~DevCfg();
	void enroll();
	void notify();
	void setUpdate(bool bUpdate);
	bool getUpdate();
public:
	static const NodeFlag nodeflag = DEVICE;
private:
	bool m_bUpdate;
	ros::Publisher m_pubFlush;
};

#endif /* DEVCFG_H_ */
