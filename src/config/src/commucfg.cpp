#include "commucfg.h"
#include "config/node_info.h"

extern ros::NodeHandle* g_pNh;

CommuCfg::CommuCfg():m_bUpdate(false)
{
	enroll();
}

CommuCfg::~CommuCfg()
{
}

void CommuCfg::enroll()
{
	m_pubFlush = g_pNh->advertise<config::node_info>("flushparam", 1000);
}

void CommuCfg::notify()
{
	config::node_info info;
	info.nodeflag = CommuCfg::nodeflag;
	m_pubFlush.publish(info);
	ROS_INFO("CommuCfg::flushparam");
}

void CommuCfg::setUpdate(bool bUpdate)
{
	m_bUpdate = bUpdate;
}

bool CommuCfg::getUpdate()
{
	return m_bUpdate;
}

