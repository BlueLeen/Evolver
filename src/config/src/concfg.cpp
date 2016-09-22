/*
 * concfg.cpp
 *
 *  Created on: Sep 18, 2016
 *      Author: su
 */

#include "concfg.h"
#include "config/node_info.h"

extern ros::NodeHandle* g_pNh;

ConCfg::ConCfg():m_bUpdate(false) {
	// TODO Auto-generated constructor stub

}

ConCfg::~ConCfg() {
	// TODO Auto-generated destructor stub
}

void ConCfg::enroll()
{
	m_pubFlush = g_pNh->advertise<config::node_info>("flushparam", 1000);
}

void ConCfg::notify()
{
	config::node_info info;
	info.nodeflag = ConCfg::nodeflag;
	m_pubFlush.publish(info);
	ROS_INFO("ConCfg::flushparam");
}

void ConCfg::setUpdate(bool bUpdate)
{
	m_bUpdate = bUpdate;
}

bool ConCfg::getUpdate()
{
	return m_bUpdate;
}

