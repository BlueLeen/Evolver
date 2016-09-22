/*
 * UpgCfg.h
 *
 *  Created on: Sep 18, 2016
 *      Author: su
 */

#ifndef CONFIGURE_UPGCFG_H_
#define CONFIGURE_UPGCFG_H_

#include <ros/ros.h>
#include "nodevent.h"
#include "common.h"

class UpgCfg : public NodEvent {
public:
	UpgCfg();
	virtual ~UpgCfg();
	void enroll();
	void notify();
	void setUpdate(bool bUpdate);
	bool getUpdate();
public:
	static const NodeFlag nodeflag = UPGRADE;
private:
	bool m_bUpdate;
	ros::Publisher m_pubFlush;
};

#endif /* UPGCFG_H_ */
