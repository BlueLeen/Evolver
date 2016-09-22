/*
 * configmanager.h
 *
 *  Created on: Sep 19, 2016
 *      Author: su
 */

#ifndef CONFIGURE_CONFIGMANAGER_H_
#define CONFIGURE_CONFIGMANAGER_H_

#include <map>
#include "cfgfile.h"
#include "common.h"
#include "config/charge_info_req.h"

class ConfigManager {
public:
	ConfigManager();
	virtual ~ConfigManager();
	void setServiceServerInit();
	bool getChargeInfo(config::charge_info_req::Request& req, config::charge_info_req::Response& res);
private:
	void initMap();
	std::map<uint8, CfgFile*> m_mapCfg;
	ros::V_Subscriber    m_vSub;
	ros::V_ServiceServer m_vServer;
	const static int SRVSIZE = 10;
};

#endif /* CONFIGMANAGER_H_ */
