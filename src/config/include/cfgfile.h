#ifndef CONFIGURE_CFGFILE_H_
#define CONFIGURE_CFGFILE_H_

class CfgFile
{
public:
	virtual ~CfgFile(){};
	virtual bool ReadConfig(const char* strFileName, void* pCfgData) = 0;
	virtual bool SaveConfig(const char* strFileName, void* pCfgData) = 0;
	virtual bool CreateConfig(const char* strFileName) = 0;
};

#endif
