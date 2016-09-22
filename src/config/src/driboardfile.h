/*
 * driboardfile.h
 *
 *  Created on: Sep 19, 2016
 *      Author: su
 */

#ifndef CONFIGURE_DRIBOARDFILE_H_
#define CONFIGURE_DRIBOARDFILE_H_

#include <cfgfile.h>

class DriboardFile: public CfgFile {
public:
	DriboardFile();
	virtual ~DriboardFile();
	bool ReadConfig(const char* strFileName, void* pCfgData);
	bool SaveConfig(const char* strFileName, void* pCfgData);
	bool CreateConfig(const char* strFileName);
public:
	//双轮补偿
	typedef struct
	{
	    float left_wheel_forward;           //左轮向前补偿
	    float left_wheel_backward;          //左轮向后补偿
	    float right_wheel_forward;          //右轮向前补偿
	    float right_wheel_backward;         //右轮向后补偿

	}WHEELS_MODIFY, *PWHEELS_MODIFY;

	//码数转距离
	typedef struct
	{
	    float cofficient_modify;            //转换系数
	    float driver_servo_interval;        //驱动伺服间隔时间（ms）

	}CODES_TO_DISTANCE, *PCODES_TO_DISTANCE_MODIFY;

	typedef struct
	{
	    char			    dest[64];
	    WHEELS_MODIFY       control_modify;             //跑直补偿
	    WHEELS_MODIFY       dead_reckon_modify;         //航位补偿
	    CODES_TO_DISTANCE   codes_to_distance;          //码数转距离
	    float               wheels_spaces_modify;       //轮间距补偿
	}DRIVER_CONFIG, *PDRIVER_CONFIG;

private:
	DRIVER_CONFIG m_dcData;
};

#endif /* DRIBOARDFILE_H_ */
