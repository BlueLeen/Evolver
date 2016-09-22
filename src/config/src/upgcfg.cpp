/*
 * UpgCfg.cpp
 *
 *  Created on: Sep 18, 2016
 *      Author: su
 */

#include "upgcfg.h"
#include "config/node_info.h"

extern ros::NodeHandle* g_pNh;

UpgCfg::UpgCfg():m_bUpdate(false) {
	// TODO Auto-generated constructor stub
	enroll();
}

UpgCfg::~UpgCfg() {
	// TODO Auto-generated destructor stub
}

void UpgCfg::enroll()
{
	m_pubFlush = g_pNh->advertise<config::node_info>("flushparam", 1000);
}

void UpgCfg::notify()
{
	config::node_info info;
	info.nodeflag = UpgCfg::nodeflag;
	m_pubFlush.publish(info);
	ROS_INFO("UpgCfg::flushparam");
}

void UpgCfg::setUpdate(bool bUpdate)
{
	m_bUpdate = bUpdate;
}

bool UpgCfg::getUpdate()
{
	return m_bUpdate;
}
