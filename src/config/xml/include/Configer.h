#ifndef __XML_CONFIGER_H__
#define __XML_CONFIGER_H__

typedef unsigned char       uint8;
typedef signed char         sint8;
typedef unsigned short      uint16;
typedef signed short        sint16;
typedef unsigned int        uint32;
typedef signed int          sint32;
typedef unsigned long       ulng32;
typedef signed long         slng32;
typedef signed long long    sint64;
typedef unsigned long long  uint64;

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

typedef struct
{
    char	dest[64];
    uint32  fan_time;                               //风机工作时间
    char    serial_num[64];                         //串行号
    uint16  infrared_init[7];                       //红外数据初始值(7个)
    uint32  charge_pile_id;                        //充电桩ID
    uint32  charge_type;                           //充电桩绑定状态
    char   charge_pile_ver[128];
    uint8 charge_channel;

}WORK_CONFIG, *PWORK_CONFIG;

typedef struct
{
    char	dest[64];
    uint32  fan_time;                               //风机工作时间
    char    serial_num[64];                         //串行号
    uint16  infrared_init[7];                       //红外数据初始值(7个)

}LOCAL_CONFIG, *PLOCAL_CONFIG;

typedef struct
{
    uint32  charge_pile_id;                        //充电桩ID
    uint32  charge_type;                           //充电桩绑定状态
    char    charge_pile_ver[128];                  //充电桩版本号
    uint32  charge_channel;                        //充电桩频段

}CHARGE_CONFIG, *PCHARGE_CONFIG;

typedef struct
{
    char    sys_version[128];                       //下位机版本号
    char    driver_version[128];                    //驱动版本号
    char    ultra_version[128];                     //超声波版本号
    char   charge_version[128];                                //充电桩类型 0-无充电桩  1-带id充电桩 2-不带id充电桩

}VERSION_CONFIG, *PVERSION_CONFIG;

//配置文件参数
typedef struct
{
    DRIVER_CONFIG       driver_config;              //驱动板配置参数
    WORK_CONFIG         work_config;                //运行配置参数
}CONFIG_DATA, *PCONFIG_DATA;

class CConfiger
{
public:
	~CConfiger();
	static	CConfiger*		GetInstance();

    bool					ReadConfig(const char* strFileName, CONFIG_DATA* pConfigData);
    bool					SetConfig(const char* strFileName, CONFIG_DATA* pConfigData);

    bool                    CreateLocalConfig(const char* strFileName);
    bool                    CreateDriverConfig(const char* strFileName);
    bool                    CreateChargeConfig(const char* strFileName);
    bool                    CreateVersionConfig(const char* strFileName);

    bool					ReadDriverConfig(const char* strFileName, DRIVER_CONFIG* pConfigData);
    bool					SetDriverConfig(const char* strFileName, DRIVER_CONFIG* pConfigData);

    bool                    ReadLocalConfig(const char* strFileName, LOCAL_CONFIG* pConfigData);
    bool                    SetLocalConfig(const char* strFileName, LOCAL_CONFIG* pConfigData);

    bool                    ReadChargeConfig(const char* strFileName, CHARGE_CONFIG* pConfigData);
    bool                    SetChargeConfig(const char* strFileName, CHARGE_CONFIG* pConfigData);

    bool					ReadWorkConfig(const char* strFileName, WORK_CONFIG* pConfigData);
    bool                    SetWorkConfig(const char* strFileName, WORK_CONFIG* pConfigData);

    bool                    ReadVersionConfig(const char* strFileName, VERSION_CONFIG* pConfigData);
    bool                    SetVersionConfig(const char* strFileName, VERSION_CONFIG* pConfigData);


private:
	CConfiger();
	static	CConfiger*		m_Instance;
};
#endif
