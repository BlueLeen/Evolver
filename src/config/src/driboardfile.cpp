/*
 * driboardfile.cpp
 *
 *  Created on: Sep 19, 2016
 *      Author: su
 */

#include "driboardfile.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "../xml/include/tinyxml.h"

#define 		STR_NODE_DRIVER_NAME					"driver"
#define         STR_NODE_CONTROL_MODIFY  				"CONTROL_MODIFY"
#define         STR_NODE_DEAD_RECKON_COMPOENSATE  		"DEAD_RECKON_COMPOENSATE"
#define     	STR_ATTR_LEFT_WHEEL_FORWARD				"left_wheel_forward"
#define     	STR_ATTR_LEFT_WHEEL_BACKWARD			"left_wheel_backward"
#define     	STR_ATTR_RIGHT_WHEEL_FORWARD			"right_wheel_forward"
#define     	STR_ATTR_RIGHT_WHEEL_BACKWARD			"right_wheel_backward"
#define         STR_NODE_CODES_TO_DISTANCE  			"CODES_TO_DISTANCE"
#define     	STR_ATTR_COFFICIENT_MODIFY				"cofficient_modify"
#define     	STR_ATTR_DRIVER_SERVO_INTERVAL			"driver_servo_interval"
#define         STR_NODE_WHEELS_SPACES_MODIFY  			"WHEELS_SPACES_MODIFY"
#define     	STR_ATTR_WHEELS_SPACES_MODIFY			"wheels_spaces_modify"

DriboardFile::DriboardFile() {
	// TODO Auto-generated constructor stub

}

DriboardFile::~DriboardFile() {
	// TODO Auto-generated destructor stub
}

bool DriboardFile::ReadConfig(const char* strFileName, void* pCfgData)
{
	PDRIVER_CONFIG pConfigData = (PDRIVER_CONFIG)pCfgData;
    if(NULL == strFileName || NULL == pConfigData)
        return false;

    TiXmlDocument tinyDoc;
    if(!tinyDoc.LoadFile(std::string(strFileName)))
    {
    	CreateConfig(strFileName);
        return false;
    }

    TiXmlElement* pRoot = tinyDoc.RootElement();
    if(NULL == pRoot)
    {
    	CreateConfig(strFileName);
        return false;
    }

    bool bFlag = false;
    TiXmlElement* pEle = pRoot->FirstChildElement();
    while(pEle)
    {
        if(0 == strcmp(pEle->FirstAttribute()->Value(), STR_NODE_DRIVER_NAME))
        {
            bFlag = true;
            break;
        }

        pEle = pEle->NextSiblingElement();
    }

    if(!bFlag)
    {
    	CreateConfig(strFileName);
        return false;
    }

    double value = 0.0;
    pEle = pEle->FirstChildElement();
    while(pEle)
    {
        if(0 == strcmp(pEle->Value(), STR_NODE_CONTROL_MODIFY))
        {
            pConfigData->control_modify.left_wheel_forward = atof(pEle->Attribute(STR_ATTR_LEFT_WHEEL_FORWARD, &value));
            pConfigData->control_modify.left_wheel_backward = atof(pEle->Attribute(STR_ATTR_LEFT_WHEEL_BACKWARD, &value));
            pConfigData->control_modify.right_wheel_forward = atof(pEle->Attribute(STR_ATTR_RIGHT_WHEEL_FORWARD, &value));
            pConfigData->control_modify.right_wheel_backward = atof(pEle->Attribute(STR_ATTR_RIGHT_WHEEL_BACKWARD, &value));
        }

        if(0 == strcmp(pEle->Value(), STR_NODE_CODES_TO_DISTANCE))
        {
            pConfigData->codes_to_distance.cofficient_modify = atof(pEle->Attribute(STR_ATTR_COFFICIENT_MODIFY, &value));
            pConfigData->codes_to_distance.driver_servo_interval = atof(pEle->Attribute(STR_ATTR_DRIVER_SERVO_INTERVAL, &value));
        }

        if(0 == strcmp(pEle->Value(), STR_NODE_DEAD_RECKON_COMPOENSATE))
        {
            pConfigData->dead_reckon_modify.left_wheel_forward = atof(pEle->Attribute(STR_ATTR_LEFT_WHEEL_FORWARD, &value));
            pConfigData->dead_reckon_modify.left_wheel_backward = atof(pEle->Attribute(STR_ATTR_LEFT_WHEEL_BACKWARD, &value));
            pConfigData->dead_reckon_modify.right_wheel_forward = atof(pEle->Attribute(STR_ATTR_RIGHT_WHEEL_FORWARD, &value));
            pConfigData->dead_reckon_modify.right_wheel_backward = atof(pEle->Attribute(STR_ATTR_RIGHT_WHEEL_BACKWARD, &value));
        }

        if(0 == strcmp(pEle->Value(), STR_NODE_WHEELS_SPACES_MODIFY))
            pConfigData->wheels_spaces_modify = atof(pEle->Attribute(STR_ATTR_WHEELS_SPACES_MODIFY, &value));

        pEle = pEle->NextSiblingElement();
    }

    return true;
}

bool DriboardFile::SaveConfig(const char* strFileName, void* pCfgData)
{
	PDRIVER_CONFIG pConfigData = (PDRIVER_CONFIG)pCfgData;
    if(NULL == strFileName || NULL == pConfigData)
        return false;

    TiXmlDocument tinyDoc;
    if(!tinyDoc.LoadFile(std::string(strFileName)))
    {
    	CreateConfig(strFileName);
        return false;
    }

    TiXmlElement* pRoot = tinyDoc.RootElement();
    if(NULL == pRoot)
    {
    	CreateConfig(strFileName);
        return false;
    }

    bool bFlag = false;
    TiXmlElement* pEle = pRoot->FirstChildElement();
    while(pEle)
    {
        if(0 == strcmp(pEle->FirstAttribute()->Value(), STR_NODE_DRIVER_NAME))
        {
            bFlag = true;
            break;
        }

        pEle = pEle->NextSiblingElement();
    }

    if(!bFlag)
    {
    	CreateConfig(strFileName);
        return false;
    }

    pEle = pEle->FirstChildElement();
    while(pEle)
    {
        if(0 == strcmp(pEle->Value(), STR_NODE_CONTROL_MODIFY))
        {
            pEle->SetDoubleAttribute(STR_ATTR_LEFT_WHEEL_FORWARD, pConfigData->control_modify.left_wheel_forward);
            pEle->SetDoubleAttribute(STR_ATTR_LEFT_WHEEL_BACKWARD, pConfigData->control_modify.left_wheel_backward);
            pEle->SetDoubleAttribute(STR_ATTR_RIGHT_WHEEL_FORWARD, pConfigData->control_modify.right_wheel_forward);
            pEle->SetDoubleAttribute(STR_ATTR_RIGHT_WHEEL_BACKWARD, pConfigData->control_modify.right_wheel_backward);
        }

        if(0 == strcmp(pEle->Value(), STR_NODE_CODES_TO_DISTANCE))
        {
            pEle->SetDoubleAttribute(STR_ATTR_COFFICIENT_MODIFY, pConfigData->codes_to_distance.cofficient_modify);
            pEle->SetDoubleAttribute(STR_ATTR_DRIVER_SERVO_INTERVAL, pConfigData->codes_to_distance.driver_servo_interval);
        }

        if(0 == strcmp(pEle->Value(), STR_NODE_DEAD_RECKON_COMPOENSATE))
        {
            pEle->SetDoubleAttribute(STR_ATTR_LEFT_WHEEL_FORWARD, pConfigData->dead_reckon_modify.left_wheel_forward);
            pEle->SetDoubleAttribute(STR_ATTR_LEFT_WHEEL_BACKWARD, pConfigData->dead_reckon_modify.left_wheel_backward);
            pEle->SetDoubleAttribute(STR_ATTR_RIGHT_WHEEL_FORWARD, pConfigData->dead_reckon_modify.right_wheel_forward);
            pEle->SetDoubleAttribute(STR_ATTR_RIGHT_WHEEL_BACKWARD, pConfigData->dead_reckon_modify.right_wheel_backward);
        }

        if(0 == strcmp(pEle->Value(), STR_NODE_WHEELS_SPACES_MODIFY))
            pEle->SetDoubleAttribute(STR_ATTR_WHEELS_SPACES_MODIFY, pConfigData->wheels_spaces_modify);

        pEle = pEle->NextSiblingElement();
    }

    tinyDoc.SaveFile(std::string(strFileName));

    return true;
}

bool DriboardFile::CreateConfig(const char* strFileName)
{
    if(NULL == strFileName)
        return false;

    TiXmlDocument* pCfgDoc = new TiXmlDocument();

    TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "utf-8", "" );
    pCfgDoc->LinkEndChild(decl);

    TiXmlElement* pEle = NULL;
    TiXmlElement* pRoot = new TiXmlElement("Root");
    pCfgDoc->LinkEndChild(pRoot);

    //driver
    TiXmlElement* pDest = new TiXmlElement("DEST");
    pDest->SetAttribute("TYPE", STR_NODE_DRIVER_NAME);
    pRoot->LinkEndChild(pDest);

    pEle = new TiXmlElement(STR_NODE_CONTROL_MODIFY);
    pEle->SetAttribute(STR_ATTR_LEFT_WHEEL_FORWARD, "");
    pEle->SetAttribute(STR_ATTR_LEFT_WHEEL_BACKWARD, "");
    pEle->SetAttribute(STR_ATTR_RIGHT_WHEEL_FORWARD, "");
    pEle->SetAttribute(STR_ATTR_RIGHT_WHEEL_BACKWARD, "");
    pDest->LinkEndChild(pEle);

    pEle = new TiXmlElement(STR_NODE_CODES_TO_DISTANCE);
    pEle->SetAttribute(STR_ATTR_COFFICIENT_MODIFY, "");
    pEle->SetAttribute(STR_ATTR_DRIVER_SERVO_INTERVAL, "");
    pDest->LinkEndChild(pEle);

    pEle = new TiXmlElement(STR_NODE_DEAD_RECKON_COMPOENSATE);
    pEle->SetAttribute(STR_ATTR_LEFT_WHEEL_FORWARD, "");
    pEle->SetAttribute(STR_ATTR_LEFT_WHEEL_BACKWARD, "");
    pEle->SetAttribute(STR_ATTR_RIGHT_WHEEL_FORWARD, "");
    pEle->SetAttribute(STR_ATTR_RIGHT_WHEEL_BACKWARD, "");
    pDest->LinkEndChild(pEle);

    pEle = new TiXmlElement(STR_NODE_WHEELS_SPACES_MODIFY);
    pEle->SetAttribute(STR_ATTR_WHEELS_SPACES_MODIFY, "");
    pDest->LinkEndChild(pEle);

    pEle = new TiXmlElement("RESERVED");
    pEle->SetAttribute("reserved_1", "");
    pEle->SetAttribute("reserved_2", "");
    pEle->SetAttribute("reserved_3", "");
    pEle->SetAttribute("reserved_4", "");
    pEle->SetAttribute("reserved_5", "");
    pEle->SetAttribute("reserved_6", "");
    pEle->SetAttribute("reserved_7", "");
    pEle->SetAttribute("reserved_8", "");
    pEle->SetAttribute("reserved_9", "");
    pEle->SetAttribute("reserved_10", "");
    pDest->LinkEndChild(pEle);

    pCfgDoc->SaveFile(strFileName);

    if(NULL != pCfgDoc)
    {
        delete pCfgDoc;
        pCfgDoc = NULL;
    }

    return true;
}

