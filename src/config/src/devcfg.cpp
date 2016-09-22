/*
 * devcfg.cpp
 *
 *  Created on: Sep 18, 2016
 *      Author: su
 */

#include "devcfg.h"
#include "config/node_info.h"

extern ros::NodeHandle* g_pNh;

DevCfg::DevCfg():m_bUpdate(false) {
	// TODO Auto-generated constructor stub
	enroll();
}

DevCfg::~DevCfg() {
	// TODO Auto-generated destructor stub
}

void DevCfg::enroll()
{
	m_pubFlush = g_pNh->advertise<config::node_info>("flushparam", 1000);
}

void DevCfg::notify()
{
	config::node_info info;
	info.nodeflag = DevCfg::nodeflag;
	m_pubFlush.publish(info);
	ROS_INFO("DevCfg::flushparam");
}

void DevCfg::setUpdate(bool bUpdate)
{
	m_bUpdate = bUpdate;
}

bool DevCfg::getUpdate()
{
	return m_bUpdate;
}

