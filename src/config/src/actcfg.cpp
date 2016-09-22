/*
 * actcfg.cpp
 *
 *  Created on: Sep 18, 2016
 *      Author: su
 */

#include "actcfg.h"
#include "config/node_info.h"

extern ros::NodeHandle* g_pNh;

ActCfg::ActCfg():m_bUpdate(false) {
	// TODO Auto-generated constructor stub
	enroll();
}

ActCfg::~ActCfg() {
	// TODO Auto-generated destructor stub
}

void ActCfg::enroll()
{
	m_pubFlush = g_pNh->advertise<config::node_info>("flushparam", 1000);
}

void ActCfg::notify()
{
	config::node_info info;
	info.nodeflag = ActCfg::nodeflag;
	m_pubFlush.publish(info);
	ROS_INFO("ActCfg::flushparam");
}

void ActCfg::setUpdate(bool bUpdate)
{
	m_bUpdate = bUpdate;
}

bool ActCfg::getUpdate()
{
	return m_bUpdate;
}

