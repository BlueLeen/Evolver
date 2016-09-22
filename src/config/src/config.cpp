#include <ros/ros.h>
//#include<boost/unordered_map.hpp>
//#include "config/node_info.h"
#include "config/node_req.h"
#include "nodevent.h"
#include "actcfg.h"
#include "commucfg.h"
#include "concfg.h"
#include "devcfg.h"
#include "sencfg.h"
#include "upgcfg.h"
#include "updatemanager.h"

#define NODENAME "config"

ros::NodeHandle* g_pNh;
//boost::unordered_map<NodeFlag, CfgEvent*> g_umNodeCfg;
NodEvent* g_umNodeCfg[UPGRADE];

void CreateNodeCfg()
{
	NodEvent* pCfg = new ActCfg();
	g_umNodeCfg[ActCfg::nodeflag - 1] = pCfg;
	pCfg = new CommuCfg();
	g_umNodeCfg[CommuCfg::nodeflag - 1] = pCfg;
	pCfg = new ConCfg();
	g_umNodeCfg[ConCfg::nodeflag - 1] = pCfg;
	pCfg = new DevCfg();
	g_umNodeCfg[DevCfg::nodeflag - 1] = pCfg;
	pCfg = new SenCfg();
	g_umNodeCfg[SenCfg::nodeflag - 1] = pCfg;
	pCfg = new UpgCfg();
	g_umNodeCfg[UpgCfg::nodeflag - 1] = pCfg;
}

void DestroyNodeCfg()
{
	for(int i=0; i<UPGRADE; i++)
		delete g_umNodeCfg[i];
}

bool request(config::node_req::Request  &req, config::node_req::Response &res)
{
	//assert node whether be valid
	if(req.info.nodeflag < ACTION || req.info.nodeflag > UPGRADE)
	{
		res.result = 0;
		return false;
	}
	g_umNodeCfg[req.info.nodeflag-1]->setUpdate(true);
	res.result = 1;
	return true;
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, NODENAME, ros::init_options::NoRosout);
	g_pNh = new ros::NodeHandle();
	CreateNodeCfg();
	UpdateManager um;
	um.start();
	ros::ServiceServer service = g_pNh->advertiseService("requestparam", request);
	ros::Rate loop_rate(10);
	while(ros::ok())
	{
		ros::spinOnce();
		loop_rate.sleep();
	}
	DestroyNodeCfg();
    delete g_pNh;
	return 0;
}
