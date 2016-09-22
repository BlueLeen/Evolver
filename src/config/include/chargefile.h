/*
 * chargefile.h
 *
 *  Created on: Sep 19, 2016
 *      Author: su
 */

#ifndef CONFIGURE_CHARGEFILE_H_
#define CONFIGURE_CHARGEFILE_H_

#include <cfgfile.h>
#include "common.h"

class ChargeFile: public CfgFile {
public:
	ChargeFile();
	virtual ~ChargeFile();
	bool ReadConfig(const char* strFileName, void* pCfgData);
	bool SaveConfig(const char* strFileName, void* pCfgData);
	bool CreateConfig(const char* strFileName);

public:
	typedef struct
	{
	    uint32  charge_pile_id;                        //充电桩ID
	    uint32  charge_type;                           //充电桩绑定状态
	    char    charge_pile_ver[128];                  //充电桩版本号
	    uint32  charge_channel;                        //充电桩频段
	}CHARGE_CONFIG, *PCHARGE_CONFIG;

private:
	CHARGE_CONFIG m_ccData;
};

#endif /* CHARGEFILE_H_ */
