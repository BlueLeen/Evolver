/*
 * configmanager.cpp
 *
 *  Created on: Sep 19, 2016
 *      Author: su
 */

#include "configmanager.h"
using std::pair;
using std::make_pair;

extern ros::NodeHandle* g_pNh;

ConfigManager::ConfigManager() {
	// TODO Auto-generated constructor stub
	initMap();
}

ConfigManager::~ConfigManager() {
	// TODO Auto-generated destructor stub
}

void ConfigManager::initMap()
{
	CfgFile* pCfgFile = new ChargeFile();
	m_mapCfg.insert(make_pair(CHARGE, pCfgFile));
	pCfgFile = new DriboardFile();
	m_mapCfg.insert(make_pair(DRIVE, pCfgFile));
}

void ConfigManager::setServiceServerInit()
{
	m_vServer.clear();
	m_vServer.resize(SRVSIZE);
	m_vServer[CHARGE-1] = g_pNh->advertiseService("get_charge_info", &ConfigManager::getChargeInfo, this);
}

bool ConfigManager::getChargeInfo(config::charge_info_req::Request& req, config::charge_info_req::Response& res)
{
	//m_mapCfg[CHARGE-1]->ReadConfig()
	res.info.chargeid = m_mapCfg[CHARGE];
	return true;
}

