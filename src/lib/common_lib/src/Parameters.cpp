/*
Copyright (c) 2010-2016, Mathieu Labbe - IntRoLab - Universite de Sherbrooke
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Universite de Sherbrooke nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "common_lib/Parameters.h"
#include <common_lib/UDirectory.h>
#include <common_lib/ULogger.h>
#include <common_lib/UConversion.h>
#include <common_lib/UStl.h>
#include <cmath>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <iomanip>
#include "common_lib/SimpleIni.h"


ParametersMap Parameters::parameters_;
ParametersMap Parameters::parametersType_;
ParametersMap Parameters::descriptions_;
Parameters Parameters::instance_;
std::map<std::string, std::pair<bool, std::string> > Parameters::removedParameters_;
ParametersMap Parameters::backwardCompatibilityMap_;

Parameters::Parameters()
{
}

Parameters::~Parameters()
{
}

std::string Parameters::serialize(const ParametersMap & parameters)
{
	std::stringstream output;
	for(ParametersMap::const_iterator iter=parameters.begin(); iter!=parameters.end(); ++iter)
	{
		if(iter != parameters.begin())
		{
			output << ";";
		}
		// make sure there are no commas instead of dots
		output << iter->first << ":" << uReplaceChar(iter->second, ',', '.');
	}
	UDEBUG("output=%s", output.str().c_str());
	return output.str();
}

ParametersMap Parameters::deserialize(const std::string & parameters)
{
	UDEBUG("parameters=%s", parameters.c_str());
	ParametersMap output;
	std::list<std::string> tuplets = uSplit(parameters, ';');
	for(std::list<std::string>::iterator iter=tuplets.begin(); iter!=tuplets.end(); ++iter)
	{
		std::list<std::string> p = uSplit(*iter, ':');
		if(p.size() == 2)
		{
			std::string key = p.front();
			std::string value = p.back();

			// look for old parameter name
			bool addParameter = true;
			std::map<std::string, std::pair<bool, std::string> >::const_iterator oldIter = Parameters::getRemovedParameters().find(key);
			if(oldIter!=Parameters::getRemovedParameters().end())
			{
				addParameter = oldIter->second.first;
				if(addParameter)
				{
					key = oldIter->second.second;
					UWARN("Parameter migration from \"%s\" to \"%s\" (value=%s).",
							oldIter->first.c_str(), oldIter->second.second.c_str(), value.c_str());
				}
				else if(oldIter->second.second.empty())
				{
					UWARN("Parameter \"%s\" doesn't exist anymore.",
								oldIter->first.c_str());
				}
				else
				{
					UWARN("Parameter \"%s\" doesn't exist anymore, you may want to use this similar parameter \"%s\":\"%s\".",
								oldIter->first.c_str(), oldIter->second.second.c_str(), Parameters::getDescription(oldIter->second.second).c_str());
				}

			}

			if(Parameters::getDefaultParameters().find(key) == Parameters::getDefaultParameters().end())
			{
				UWARN("Unknown parameter \"%s\"=\"%s\"! The parameter is still added to output map.", key.c_str(), value.c_str());
			}
			uInsert(output, ParametersPair(key, value));
		}
	}
	return output;
}


ParametersMap Parameters::getDefaultParameters(const std::string & group)
{
	ParametersMap parameters;
	const ParametersMap & defaultParameters = Parameters::getDefaultParameters();
	for(ParametersMap::const_iterator iter=defaultParameters.begin(); iter!=defaultParameters.end(); ++iter)
	{
		if(iter->first.compare(group) == 0)
		{
			parameters.insert(*iter);
		}
	}
	UASSERT_MSG(parameters.size(), uFormat("No parameters found for group %s!", group.c_str()).c_str());
	return parameters;
}

ParametersMap Parameters::filterParameters(const ParametersMap & parameters, const std::string & group)
{
	ParametersMap output;
	for(ParametersMap::const_iterator iter=parameters.begin(); iter!=parameters.end(); ++iter)
	{
		if(iter->first.compare(group) == 0)
		{
			output.insert(*iter);
		}
	}
	return output;
}

const std::map<std::string, std::pair<bool, std::string> > & Parameters::getRemovedParameters()
{
	if(removedParameters_.empty())
	{
        /*
	    removedParameters_.insert(std::make_pair("Odom/LocalHistory",                std::make_pair(true, Parameters::kOdomF2MMaxSize())));
		removedParameters_.insert(std::make_pair("Odom/NearestNeighbor",             std::make_pair(true, Parameters::kVisCorNNType())));
		removedParameters_.insert(std::make_pair("Odom/NNDR",                        std::make_pair(true, Parameters::kVisCorNNDR())));
		*/
	}
	return removedParameters_;
}

const ParametersMap & Parameters::getBackwardCompatibilityMap()
{
	if(backwardCompatibilityMap_.empty())
	{
		getRemovedParameters(); // make sure removedParameters is filled

		// compatibility
		for(std::map<std::string, std::pair<bool, std::string> >::iterator iter=removedParameters_.begin();
			iter!=removedParameters_.end();
			++iter)
		{
			if(iter->second.first)
			{
				backwardCompatibilityMap_.insert(ParametersPair(iter->second.second, iter->first));
			}
		}
	}
	return backwardCompatibilityMap_;
}

std::string Parameters::getType(const std::string & paramKey)
{
	std::string type;
	ParametersMap::iterator iter = parametersType_.find(paramKey);
	if(iter != parametersType_.end())
	{
		type = iter->second;
	}
	else
	{
		UERROR("Parameters \"%s\" doesn't exist!", paramKey.c_str());
	}
	return type;
}

std::string Parameters::getDescription(const std::string & paramKey)
{
	std::string description;
	ParametersMap::iterator iter = descriptions_.find(paramKey);
	if(iter != descriptions_.end())
	{
		description = iter->second;
	}
	else
	{
		UERROR("Parameters \"%s\" doesn't exist!", paramKey.c_str());
	}
	return description;
}

void Parameters::parse(const ParametersMap & parameters, const std::string & key, bool & value)
{
	ParametersMap::const_iterator iter = parameters.find(key);
	if(iter != parameters.end())
	{
		value = uStr2Bool(iter->second.c_str());
	}
}
void Parameters::parse(const ParametersMap & parameters, const std::string & key, int & value)
{
	ParametersMap::const_iterator iter = parameters.find(key);
	if(iter != parameters.end())
	{
		value = uStr2Int(iter->second.c_str());
	}
}
void Parameters::parse(const ParametersMap & parameters, const std::string & key, unsigned int & value)
{
	ParametersMap::const_iterator iter = parameters.find(key);
	if(iter != parameters.end())
	{
		value = uStr2Int(iter->second.c_str());
	}
}
void Parameters::parse(const ParametersMap & parameters, const std::string & key, float & value)
{
	ParametersMap::const_iterator iter = parameters.find(key);
	if(iter != parameters.end())
	{
		value = uStr2Float(iter->second);
	}
}
void Parameters::parse(const ParametersMap & parameters, const std::string & key, double & value)
{
	ParametersMap::const_iterator iter = parameters.find(key);
	if(iter != parameters.end())
	{
		value = uStr2Double(iter->second);
	}
}
void Parameters::parse(const ParametersMap & parameters, const std::string & key, std::string & value)
{
	ParametersMap::const_iterator iter = parameters.find(key);
	if(iter != parameters.end())
	{
		value = iter->second;
	}
}
void Parameters::parse(const ParametersMap & parameters, ParametersMap & parametersOut)
{
	for(ParametersMap::iterator iter=parametersOut.begin(); iter!=parametersOut.end(); ++iter)
	{
		ParametersMap::const_iterator jter = parameters.find(iter->first);
		if(jter != parameters.end())
		{
			iter->second = jter->second;
		}
	}
}

const char * Parameters::showUsage()
{
	return  "Logger options:\n"
			"   --nolog              Disable logger\n"
			"   --logconsole         Set logger console type\n"
			"   --logfile \"path\"     Set logger file type\n"
			"   --logfilea \"path\"    Set logger file type with appending mode if the file already exists\n"
			"   --udebug             Set logger level to debug\n"
			"   --uinfo              Set logger level to info\n"
			"   --uwarn              Set logger level to warn\n"
			"   --uerror             Set logger level to error\n"
			"   --logtime \"bool\"     Print time when logging\n"
			"   --logwhere \"bool\"    Print where when logging\n"
			"   --logthread \"bool\"   Print thread id when logging\n"
			"RTAB-Map options:\n"
			"   --params                       Show all parameters with their default value and description\n"
			"   --\"parameter name\" \"value\"     Overwrite a specific RTAB-Map's parameter :\n"
			"                                    --SURF/HessianThreshold 150\n"
			"                                   For parameters in table format, add ',' between values :\n"
			"                                    --Kp/RoiRatios 0,0,0.1,0\n"
			;
}

ParametersMap Parameters::parseArguments(int argc, char * argv[])
{
	ParametersMap out;
	const ParametersMap & parameters = getDefaultParameters();
	const std::map<std::string, std::pair<bool, std::string> > & removedParams = getRemovedParameters();
	for(int i=0;i<argc;++i)
	{
		if(strcmp(argv[i], "--nolog") == 0)
		{
			ULogger::setType(ULogger::kTypeNoLog);
		}
		else if(strcmp(argv[i], "--logconsole") == 0)
		{
			ULogger::setType(ULogger::kTypeConsole);
		}
		else if(strcmp(argv[i], "--logfile") == 0)
		{
			++i;
			if(i < argc)
			{
				ULogger::setType(ULogger::kTypeFile, argv[i], false);
			}
			else
			{
				UERROR("\"--logfile\" argument requires following file path");
			}
		}
		else if(strcmp(argv[i], "--logfilea") == 0)
		{
			++i;
			if(i < argc)
			{
				ULogger::setType(ULogger::kTypeFile, argv[i], true);
			}
			else
			{
				UERROR("\"--logfilea\" argument requires following file path");
			}
		}
		else if(strcmp(argv[i], "--udebug") == 0)
		{
			ULogger::setLevel(ULogger::kDebug);
		}
		else if(strcmp(argv[i], "--uinfo") == 0)
		{
			ULogger::setLevel(ULogger::kInfo);
		}
		else if(strcmp(argv[i], "--uwarn") == 0)
		{
			ULogger::setLevel(ULogger::kWarning);
		}
		else if(strcmp(argv[i], "--uerror") == 0)
		{
			ULogger::setLevel(ULogger::kError);
		}
		else if(strcmp(argv[i], "--ulogtime") == 0)
		{
			++i;
			if(i < argc)
			{
				ULogger::setPrintTime(uStr2Bool(argv[i]));
			}
			else
			{
				UERROR("\"--ulogtime\" argument requires a following boolean value");
			}
		}
		else if(strcmp(argv[i], "--ulogwhere") == 0)
		{
			++i;
			if(i < argc)
			{
				ULogger::setPrintWhere(uStr2Bool(argv[i]));
			}
			else
			{
				UERROR("\"--ulogwhere\" argument requires a following boolean value");
			}
		}
		else if(strcmp(argv[i], "--ulogthread") == 0)
		{
			++i;
			if(i < argc)
			{
				ULogger::setPrintThreadId(uStr2Bool(argv[i]));
			}
			else
			{
				UERROR("\"--ulogthread\" argument requires a following boolean value");
			}
		}
		else if(strcmp(argv[i], "--params") == 0)
		{
			for(ParametersMap::const_iterator iter=parameters.begin(); iter!=parameters.end(); ++iter)
			{
				std::string str = "Param: " + iter->first + " = \"" + iter->second + "\"";
				std::cout <<
						str <<
						std::setw(60 - str.size()) <<
						" [" <<
						Parameters::getDescription(iter->first).c_str() <<
						"]" <<
						std::endl;
			}
			UWARN("App will now exit after showing default RTAB-Map parameters because "
					 "argument \"--params\" is detected!");
			exit(0);
		}
		else // check for parameters
		{
			std::string key = uReplaceChar(argv[i], '-', "");
			ParametersMap::const_iterator iter = parameters.find(key);
			if(iter != parameters.end())
			{
				++i;
				if(i < argc)
				{
					uInsert(out, ParametersPair(iter->first, argv[i]));
				}
			}
			else
			{
				// backward compatibility
				std::map<std::string, std::pair<bool, std::string> >::const_iterator jter = removedParams.find(key);
				if(jter!=removedParams.end())
				{
					if(jter->second.first)
					{
						++i;
						if(i < argc)
						{
							std::string value = argv[i];
							if(!value.empty())
							{
								value = uReplaceChar(value, ',', ' '); // for table
								key = jter->second.second;
								UWARN("Parameter migration from \"%s\" to \"%s\" (value=%s).",
										jter->first.c_str(), jter->second.second.c_str(), value.c_str());
								uInsert(out, ParametersPair(key, value));
							}
						}
						else
						{
							UERROR("Value missing for argument \"%s\"", argv[i-1]);
						}
					}
					else if(jter->second.second.empty())
					{
						UERROR("Parameter \"%s\" doesn't exist anymore.", jter->first.c_str());
					}
					else
					{
						UERROR("Parameter \"%s\" doesn't exist anymore, check this similar parameter \"%s\".", jter->first.c_str(), jter->second.second.c_str());
					}
				}
			}
		}
	}
	return out;
}


void Parameters::readINI(const std::string & configFile, ParametersMap & parameters)
{
	CSimpleIniA ini;
	ini.LoadFile(configFile.c_str());
	const CSimpleIniA::TKeyVal * keyValMap = ini.GetSection("Core");
	if(keyValMap)
	{
		for(CSimpleIniA::TKeyVal::const_iterator iter=keyValMap->begin(); iter!=keyValMap->end(); ++iter)
		{
			std::string key = (*iter).first.pItem;
			if(key.compare("Version") == 0)
			{
				// Compare version in ini with the current RTAB-Map version
				std::vector<std::string> version = uListToVector(uSplit((*iter).second, '.'));
				if(version.size() == 3)
				{
				    /*
					if(!RTABMAP_VERSION_COMPARE(std::atoi(version[0].c_str()), std::atoi(version[1].c_str()), std::atoi(version[2].c_str())))
					{
						if(configFile.find(".rtabmap") != std::string::npos)
						{
							UWARN("Version in the config file \"%s\" is more recent (\"%s\") than "
								   "current RTAB-Map version used (\"%s\"). The config file will be upgraded "
								   "to new version.",
								   configFile.c_str(),
								   (*iter).second,
								   RTABMAP_VERSION);
						}
						else
						{
							UERROR("Version in the config file \"%s\" is more recent (\"%s\") than "
								   "current RTAB-Map version used (\"%s\"). New parameters (if there are some) will "
								   "be ignored.",
								   configFile.c_str(),
								   (*iter).second,
								   RTABMAP_VERSION);
						}
					}
					*/
				}
			}
			else
			{
				key = uReplaceChar(key, '\\', '/'); // Ini files use \ by default for separators, so replace them

				// look for old parameter name
				bool addParameter = true;
				std::map<std::string, std::pair<bool, std::string> >::const_iterator oldIter = Parameters::getRemovedParameters().find(key);
				if(oldIter!=Parameters::getRemovedParameters().end())
				{
					addParameter = oldIter->second.first;
					if(addParameter)
					{
						key = oldIter->second.second;
						UWARN("Parameter migration from \"%s\" to \"%s\" (value=%s).",
								oldIter->first.c_str(), oldIter->second.second.c_str(), iter->second);
					}
					else if(oldIter->second.second.empty())
					{
						UWARN("Parameter \"%s\" doesn't exist anymore.",
									oldIter->first.c_str());
					}
					else
					{
						UWARN("Parameter \"%s\" doesn't exist anymore, you may want to use this similar parameter \"%s\":\"%s\".",
									oldIter->first.c_str(), oldIter->second.second.c_str(), Parameters::getDescription(oldIter->second.second).c_str());
					}

				}

				if(Parameters::getDefaultParameters().find(key) != Parameters::getDefaultParameters().end())
				{
					uInsert(parameters, ParametersPair(key, iter->second));
				}
			}
		}
	}
	else
	{
		ULOGGER_WARN("Section \"Core\" in %s doesn't exist... "
				    "Ignore this warning if the ini file does not exist yet. "
				    "The ini file will be automatically created when this node will close.", configFile.c_str());
	}
}

void Parameters::writeINI(const std::string & configFile, const ParametersMap & parameters)
{
	CSimpleIniA ini;
	ini.LoadFile(configFile.c_str());

	// Save current version
	//ini.SetValue("Core", "Version", RTABMAP_VERSION, NULL, true);

	for(ParametersMap::const_iterator i=parameters.begin(); i!=parameters.end(); ++i)
	{
		std::string key = (*i).first;
		key = uReplaceChar(key, '/', '\\'); // Ini files use \ by default for separators, so replace the /
		ini.SetValue("Core", key.c_str(), (*i).second.c_str(), NULL, true);
	}

	ini.SaveFile(configFile.c_str());
}
