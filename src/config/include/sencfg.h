/*
 * sencfg.h
 *
 *  Created on: Sep 18, 2016
 *      Author: su
 */

#ifndef CONFIGURE_SENCFG_H_
#define CONFIGURE_SENCFG_H_

#include <ros/ros.h>
#include "nodevent.h"
#include "common.h"

class SenCfg : public NodEvent {
public:
	SenCfg();
	virtual ~SenCfg();
	void enroll();
	void notify();
	void setUpdate(bool bUpdate);
	bool getUpdate();
public:
	static const NodeFlag nodeflag = SENSOR;
private:
	bool m_bUpdate;
	ros::Publisher m_pubFlush;
};

#endif /* SENCFG_H_ */
