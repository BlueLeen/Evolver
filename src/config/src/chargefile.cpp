/*
 * chargefile.cpp
 *
 *  Created on: Sep 19, 2016
 *      Author: su
 */

#include "chargefile.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "../xml/include/tinyxml.h"

#define 		STR_NODE_CHARGE_NAME					"charge"
#define         STR_NODE_CHARGE_ID                		"CHARGE_ID"
#define     	STR_ATTR_CHARGE_ID           			"charge_id"
#define         STR_NODE_CHARGE_TYPE              		"CHARGE_TYPE"
//#define     	STR_ATTR_CHARGE_TPYE          			"charge_tpye"
#define     	STR_ATTR_CHARGE_TYPE          			"charge_type"
#define         STR_NODE_CHARGE_VER              		"CHARGE_VER"
#define     	STR_ATTR_CHARGE_VER          			"charge_ver"
#define         STR_NODE_CHARGE_CHANNEL             	"CHARGE_CHANNEL"
#define     	STR_ATTR_CHARGE_CHANNEL         		"charge_channel"

ChargeFile::ChargeFile() {
	// TODO Auto-generated constructor stub

}

ChargeFile::~ChargeFile() {
	// TODO Auto-generated destructor stub
}

bool ChargeFile::ReadConfig(const char* strFileName, void* pCfgData)
{
	PCHARGE_CONFIG pConfigData = (PCHARGE_CONFIG)pCfgData;
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
        if(0 == strcmp(pEle->FirstAttribute()->Value(), STR_NODE_CHARGE_NAME))
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

    int value_local = 0;
    pEle = pEle->FirstChildElement();
    while(pEle)
    {
        if(0 == strcmp(pEle->Value(), STR_NODE_CHARGE_ID))
            pConfigData->charge_pile_id = atoi(pEle->Attribute(STR_ATTR_CHARGE_ID, &value_local));

        if(0 == strcmp(pEle->Value(), STR_NODE_CHARGE_TYPE))
            pConfigData->charge_type = atoi(pEle->Attribute(STR_ATTR_CHARGE_TYPE, &value_local));

        if(0 == strcmp(pEle->Value(), STR_NODE_CHARGE_VER))
            strcpy(pConfigData->charge_pile_ver, pEle->Attribute(STR_ATTR_CHARGE_VER));

        if(0 == strcmp(pEle->Value(), STR_NODE_CHARGE_CHANNEL))
            pConfigData->charge_channel = atoi(pEle->Attribute(STR_ATTR_CHARGE_CHANNEL, &value_local));

        pEle = pEle->NextSiblingElement();
    }
	return true;
}

bool ChargeFile::SaveConfig(const char* strFileName, void* pCfgData)
{
	PCHARGE_CONFIG pConfigData = (PCHARGE_CONFIG)pCfgData;
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
        if(0 == strcmp(pEle->FirstAttribute()->Value(), STR_NODE_CHARGE_NAME))
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
        if(0 == strcmp(pEle->Value(), STR_NODE_CHARGE_ID))
            pEle->SetAttribute(STR_ATTR_CHARGE_ID, pConfigData->charge_pile_id);

        if(0 == strcmp(pEle->Value(), STR_NODE_CHARGE_TYPE))
            pEle->SetAttribute(STR_ATTR_CHARGE_TYPE, pConfigData->charge_type);

        if(0 == strcmp(pEle->Value(), STR_NODE_CHARGE_VER))
            pEle->SetAttribute(STR_ATTR_CHARGE_VER, pConfigData->charge_pile_ver);

        if(0 == strcmp(pEle->Value(), STR_NODE_CHARGE_CHANNEL))
            pEle->SetAttribute(STR_ATTR_CHARGE_CHANNEL, pConfigData->charge_channel);


        pEle = pEle->NextSiblingElement();
    }

    tinyDoc.SaveFile(std::string(strFileName));
    return true;
}

bool ChargeFile::CreateConfig(const char* strFileName)
{
    if(NULL == strFileName)
        return false;

    TiXmlDocument* pCfgDoc = new TiXmlDocument();

    TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "utf-8", "" );
    pCfgDoc->LinkEndChild(decl);

    TiXmlElement* pEle = NULL;
    TiXmlElement* pRoot = new TiXmlElement("Root");
    pCfgDoc->LinkEndChild(pRoot);

    //charge
    TiXmlElement* pDestCharge = new TiXmlElement("DEST");
    pDestCharge->SetAttribute("TYPE", STR_NODE_CHARGE_NAME);
    pRoot->LinkEndChild(pDestCharge);

    pEle = new TiXmlElement(STR_NODE_CHARGE_ID);
    pEle->SetAttribute(STR_ATTR_CHARGE_ID, "10000");
    pDestCharge->LinkEndChild(pEle);

    pEle = new TiXmlElement(STR_NODE_CHARGE_TYPE);
    pEle->SetAttribute(STR_ATTR_CHARGE_TYPE, "");
    pDestCharge->LinkEndChild(pEle);

    pEle = new TiXmlElement(STR_NODE_CHARGE_VER);
    pEle->SetAttribute(STR_ATTR_CHARGE_VER, "");
    pDestCharge->LinkEndChild(pEle);

    pEle = new TiXmlElement(STR_NODE_CHARGE_CHANNEL);
    pEle->SetAttribute(STR_ATTR_CHARGE_CHANNEL, "");
    pDestCharge->LinkEndChild(pEle);

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
    pDestCharge->LinkEndChild(pEle);

    pCfgDoc->SaveFile(strFileName);

    if(NULL != pCfgDoc)
    {
        delete pCfgDoc;
        pCfgDoc = NULL;
    }

    return true;
}

