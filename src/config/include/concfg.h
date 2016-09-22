/*
 * concfg.h
 *
 *  Created on: Sep 18, 2016
 *      Author: su
 */

#ifndef CONFIGURE_CONCFG_H_
#define CONFIGURE_CONCFG_H_

#include <ros/ros.h>
#include "nodevent.h"
#include "common.h"

class ConCfg : public NodEvent {
public:
	ConCfg();
	virtual ~ConCfg();
	void enroll();
	void notify();
	void setUpdate(bool bUpdate);
	bool getUpdate();
public:
	static const NodeFlag nodeflag = CONFIG;
private:
	bool m_bUpdate;
	ros::Publisher m_pubFlush;
};

#endif /* CONCFG_H_ */
