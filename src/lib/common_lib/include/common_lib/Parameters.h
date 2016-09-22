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

#ifndef PARAMETERS_H_
#define PARAMETERS_H_

// default parameters
#include "common_lib/RtabmapExp.h" // DLL export/import defines
#include <string>
#include <map>


typedef std::map<std::string, std::string> ParametersMap; // Key, value
typedef std::pair<std::string, std::string> ParametersPair;

/**
 * Macro used to create parameter's key and default value.
 * This macro must be used only in the Parameters class definition (in this file).
 * They are automatically added to the default parameters map of the class Parameters.
 * Example:
 * @code
 * 		//for PARAM(Video, ImageWidth, int, 640), the output will be :
 * 		public:
 * 			static std::string kVideoImageWidth() {return std::string("Video/ImageWidth");}
 * 			static int defaultVideoImageWidth() {return 640;}
 * 		private:
 * 			class DummyVideoImageWidth {
 * 			public:
 * 				DummyVideoImageWidth() {parameters_.insert(ParametersPair("Video/ImageWidth", "640"));}
 * 			};
 * 			DummyVideoImageWidth dummyVideoImageWidth;
 * @endcode
 */
#define EVOLVER_PARAM(PREFIX, NAME, TYPE, DEFAULT_VALUE, DESCRIPTION) \
	public: \
		static std::string k##PREFIX##NAME() {return std::string(#PREFIX "/" #NAME);} \
		static TYPE default##PREFIX##NAME() {return DEFAULT_VALUE;} \
		static std::string type##PREFIX##NAME() {return std::string(#TYPE);} \
	private: \
		class Dummy##PREFIX##NAME { \
		public: \
			Dummy##PREFIX##NAME() {parameters_.insert(ParametersPair(#PREFIX "/" #NAME, #DEFAULT_VALUE)); \
								   parametersType_.insert(ParametersPair(#PREFIX "/" #NAME, #TYPE)); \
								   descriptions_.insert(ParametersPair(#PREFIX "/" #NAME, DESCRIPTION));} \
		}; \
		Dummy##PREFIX##NAME dummy##PREFIX##NAME;
// end define PARAM

/**
 * It's the same as the macro PARAM but it should be used for string parameters.
 * Macro used to create parameter's key and default value.
 * This macro must be used only in the Parameters class definition (in this file).
 * They are automatically added to the default parameters map of the class Parameters.
 * Example:
 * @code
 * 		//for PARAM_STR(Video, TextFileName, "Hello_world"), the output will be :
 * 		public:
 * 			static std::string kVideoFileName() {return std::string("Video/FileName");}
 * 			static std::string defaultVideoFileName() {return "Hello_world";}
 * 		private:
 * 			class DummyVideoFileName {
 * 			public:
 * 				DummyVideoFileName() {parameters_.insert(ParametersPair("Video/FileName", "Hello_world"));}
 * 			};
 * 			DummyVideoFileName dummyVideoFileName;
 * @endcode
 */
#define EVOLVER_PARAM_STR(PREFIX, NAME, DEFAULT_VALUE, DESCRIPTION) \
	public: \
		static std::string k##PREFIX##NAME() {return std::string(#PREFIX "/" #NAME);} \
		static std::string default##PREFIX##NAME() {return DEFAULT_VALUE;} \
		static std::string type##PREFIX##NAME() {return std::string("string");} \
	private: \
		class Dummy##PREFIX##NAME { \
		public: \
			Dummy##PREFIX##NAME() {parameters_.insert(ParametersPair(#PREFIX "/" #NAME, DEFAULT_VALUE)); \
								   parametersType_.insert(ParametersPair(#PREFIX "/" #NAME, "string")); \
								   descriptions_.insert(ParametersPair(#PREFIX "/" #NAME, DESCRIPTION));} \
		}; \
		Dummy##PREFIX##NAME dummy##PREFIX##NAME;
// end define PARAM

/**
 * Macro used to create parameter's key and default value.
 * This macro must be used only in the Parameters class definition (in this file).
 * They are automatically added to the default parameters map of the class Parameters.
 * Example:
 * @code
 * 		//for PARAM(Video, ImageWidth, int, 640), the output will be :
 * 		public:
 * 			static std::string kVideoImageWidth() {return std::string("Video/ImageWidth");}
 * 			static int defaultVideoImageWidth() {return 640;}
 * 		private:
 * 			class DummyVideoImageWidth {
 * 			public:
 * 				DummyVideoImageWidth() {parameters_.insert(ParametersPair("Video/ImageWidth", "640"));}
 * 			};
 * 			DummyVideoImageWidth dummyVideoImageWidth;
 * @endcode
 */
#define EVOLVER_PARAM_COND(PREFIX, NAME, TYPE, COND, DEFAULT_VALUE1, DEFAULT_VALUE2, DESCRIPTION) \
	public: \
		static std::string k##PREFIX##NAME() {return std::string(#PREFIX "/" #NAME);} \
		static TYPE default##PREFIX##NAME() {return COND?DEFAULT_VALUE1:DEFAULT_VALUE2;} \
		static std::string type##PREFIX##NAME() {return std::string(#TYPE);} \
	private: \
		class Dummy##PREFIX##NAME { \
		public: \
			Dummy##PREFIX##NAME() {parameters_.insert(ParametersPair(#PREFIX "/" #NAME, COND?#DEFAULT_VALUE1:#DEFAULT_VALUE2)); \
								   parametersType_.insert(ParametersPair(#PREFIX "/" #NAME, #TYPE)); \
								   descriptions_.insert(ParametersPair(#PREFIX "/" #NAME, DESCRIPTION));} \
		}; \
		Dummy##PREFIX##NAME dummy##PREFIX##NAME;
// end define PARAM

/**
 * Class Parameters.
 * This class is used to manage all custom parameters
 * we want in the application. It was designed to be very easy to add
 * a new parameter (just by adding one line of code).
 * The macro PARAM(PREFIX, NAME, TYPE, DEFAULT_VALUE) is
 * used to create a parameter in this class. A parameter can be accessed after by
 * Parameters::defaultPARAMETERNAME() for the default value, Parameters::kPARAMETERNAME for his key (parameter name).
 * The class provides also a general map containing all the parameter's key and
 * default value. This map can be accessed anywhere in the application by
 * Parameters::getDefaultParameters();
 * Example:
 * @code
 * 		//Defining a parameter in this class with the macro PARAM:
 * 		PARAM(Video, ImageWidth, int, 640);
 *
 * 		// Now from anywhere in the application (Parameters is a singleton)
 * 		int width = Parameters::defaultVideoImageWidth(); // theDefaultValue = 640
 * 		std::string theKey = Parameters::kVideoImageWidth(); // theKey = "Video/ImageWidth"
 * 		std::string strValue = Util::value(Parameters::getDefaultParameters(), theKey); // strValue = "640"
 * @endcode
 * @see getDefaultParameters()
 * TODO Add a detailed example with simple classes
 */
class  Parameters
{
	// EVOLVER parameters
	EVOLVER_PARAM(Map,     Strategy, 	                 int, 8,     "grip 0, Probability 1");
	EVOLVER_PARAM(Map,     Height, 	                 int , 800, "map size of height.");
	EVOLVER_PARAM(Map, Width, 	                     int , 600, "map size of width.");
	EVOLVER_PARAM(Map, CellSize, 	                 int,  400, "Unit grid size.");

	EVOLVER_PARAM(PathPlann,Strategy, 	         int, 0, "A* 0,A** 1,A*** 3");
	EVOLVER_PARAM(PathPlann, Dwa, 		             bool, false,   "0 not startup,1 startup ");
	EVOLVER_PARAM_STR(Map, StoragePath, "~/navigation", 		"where the map info locate.");

public:
	virtual ~Parameters();

	/**
	 * Get default parameters
	 *
	 */
	static const ParametersMap & getDefaultParameters()
	{
		return parameters_;
	}
	
	/**
	 * Get parameter type
	 *
	 */
	static std::string getType(const std::string & paramKey);

	/**
	 * Get parameter description
	 *
	 */
	static std::string getDescription(const std::string & paramKey);

	static void parse(const ParametersMap & parameters, const std::string & key, bool & value);
	static void parse(const ParametersMap & parameters, const std::string & key, int & value);
	static void parse(const ParametersMap & parameters, const std::string & key, unsigned int & value);
	static void parse(const ParametersMap & parameters, const std::string & key, float & value);
	static void parse(const ParametersMap & parameters, const std::string & key, double & value);
	static void parse(const ParametersMap & parameters, const std::string & key, std::string & value);
	static void parse(const ParametersMap & parameters, ParametersMap & parametersOut);

	static const char * showUsage();
	static ParametersMap parseArguments(int argc, char * argv[]);

	static std::string getVersion();
	static std::string getDefaultDatabaseName();
	
	static std::string serialize(const ParametersMap & parameters);
	static ParametersMap deserialize(const std::string & parameters);

	static bool isFeatureParameter(const std::string & param);
	static ParametersMap getDefaultOdometryParameters(bool stereo = false);
	static ParametersMap getDefaultParameters(const std::string & group);
	static ParametersMap filterParameters(const ParametersMap & parameters, const std::string & group);

	static void readINI(const std::string & configFile, ParametersMap & parameters);
	static void writeINI(const std::string & configFile, const ParametersMap & parameters);

	/**
	 * Get removed parameters (backward compatibility)
	 * <OldKeyName, <isEqual, NewKeyName> >, when isEqual=true, the old value can be safely copied to new parameter
	 */
	static const std::map<std::string, std::pair<bool, std::string> > & getRemovedParameters();
	
	/**
	 * <NewKeyName, OldKeyName>
	 */
	static const ParametersMap & getBackwardCompatibilityMap();

	static std::string createDefaultWorkingDirectory();

private:
	Parameters();

private:
	static ParametersMap parameters_;
	static ParametersMap parametersType_;
	static ParametersMap descriptions_;
	static Parameters instance_;
	
	static std::map<std::string, std::pair<bool, std::string> > removedParameters_;
	static ParametersMap backwardCompatibilityMap_;
};

#endif /* PARAMETERS_H_ */

