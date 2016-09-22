/*
 * sencfg.cpp
 *
 *  Created on: Sep 18, 2016
 *      Author: su
 */

#include "sencfg.h"
#include "config/node_info.h"

extern ros::NodeHandle* g_pNh;

SenCfg::SenCfg():m_bUpdate(false) {
	// TODO Auto-generated constructor stub
	enroll();
}

SenCfg::~SenCfg() {
	// TODO Auto-generated destructor stub
}

void SenCfg::enroll()
{
	m_pubFlush = g_pNh->advertise<config::node_info>("flushparam", 1000);
}

void SenCfg::notify()
{
	config::node_info info;
	info.nodeflag = SenCfg::nodeflag;
	m_pubFlush.publish(info);
	ROS_INFO("CommuCfg::flushparam");
}

void SenCfg::setUpdate(bool bUpdate)
{
	m_bUpdate = bUpdate;
}

bool SenCfg::getUpdate()
{
	return m_bUpdate;
}
