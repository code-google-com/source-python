/**
* =============================================================================
* Source Python
* Copyright (C) 2012 Source Python Development Team.  All rights reserved.
* =============================================================================
*
* This program is free software; you can redistribute it and/or modify it under
* the terms of the GNU General Public License, version 3.0, as published by the
* Free Software Foundation.
* 
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
* FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
* details.
*
* You should have received a copy of the GNU General Public License along with
* this program.  If not, see <http://www.gnu.org/licenses/>.
*
* As a special exception, the Source Python Team gives you permission 
* to link the code of this program (as well as its derivative works) to 
* "Half-Life 2," the "Source Engine," and any Game MODs that run on software
* by the Valve Corporation.  You must obey the GNU General Public License in
* all respects for all other code used.  Additionally, the Source.Python
* Development Team grants this exception to all derivative works.  
*/

//---------------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------------
#include "entity_props.h"
#include "../export_main.h"
#include "core/sp_python.h"
#include "utility/wrap_macros.h"
#include "utility/sp_util.h"
#include "eiface.h"
#include "dt_common.h"
#include "dt_send.h"
#include "server_class.h"
#include "boost/unordered_map.hpp"

//---------------------------------------------------------------------------------
// Namespaces to use.
//---------------------------------------------------------------------------------
using namespace boost::python;

//---------------------------------------------------------------------------------
// External variables to use.
//---------------------------------------------------------------------------------
extern IServerGameDLL* servergamedll;

struct OffsetDefinition
{
public:
	OffsetDefinition(int iOffset, SendPropType type):
	    m_iOffset(iOffset), m_type(type)
	{
	}
	OffsetDefinition():
		m_iOffset(0), m_type(DPT_Int)
	{
	}
	int m_iOffset;
	SendPropType m_type;
};

typedef boost::unordered_map<std::string, OffsetDefinition> OffsetMap;
OffsetMap g_OffsetMap;

//---------------------------------------------------------------------------------
// A helper method to return split a path down in order to recurse down the path
// to search for a network property's offset.
//---------------------------------------------------------------------------------
void SplitPath(const char* szFullPath, char* szClassName, char* szTempPath)
{
    if (!szFullPath || !szClassName || !szTempPath)
    {
        return;
    }

    int i = 0;
    while(szFullPath[i] != '\0' && szFullPath[i] != '.')
    {
        szClassName[i] = szFullPath[i];
        i++;
    }
    szClassName[i]='\0';
    int j = 0;
    while(szFullPath[i] != '\0')
    {
        i++;
        szTempPath[j] = szFullPath[i];
        j++;
    }
    szTempPath[j]='\0';
}

//---------------------------------------------------------------------------------
// Searches the current class' parameters (recursively) until the full property
// path has been reached, which returns true if a valid value has been found, and
// false if not. iOffset and pType are passed as out parameters, which will contain
// the final offset and the type of the property if found.
//---------------------------------------------------------------------------------
bool GetPropOffsetInTable(SendTable* pTable, char* szRemainPath, int* iOffset, SendPropType* pType)
{
    char szTempPath[2048];
    strcpy(szTempPath, szRemainPath);
    char szValueName[1024];
    SplitPath(szRemainPath, szValueName, szTempPath);
    int NumProps = pTable->GetNumProps();
    for (int i=0; i<NumProps; i++)
    {
        SendProp* pProp = pTable->GetProp(i);
		if (strcmp(szValueName, pProp->GetName()) == 0)
        {
            bool bValueOutput = false;
            *iOffset = *iOffset + pProp->GetOffset();
            *pType = pProp->GetType();
            switch (pProp->GetType())
            {
            case DPT_Vector:
            case DPT_String:
            case DPT_Array:
            case DPT_Int:
            case DPT_Float:
                return true;
            case DPT_DataTable:
                return GetPropOffsetInTable(pProp->GetDataTable(), szTempPath, iOffset, pType);
                break;
            default:
                *iOffset = 0;
                return false; 
            }
        }
    }
    return false;
}

//---------------------------------------------------------------------------------
// Gets the offset of a network prop from the base of an edict_t instance.
//---------------------------------------------------------------------------------
bool GetPropOffset(const char* szFullPath, int* iOffset, SendPropType* pType)
{
	OffsetMap::iterator offsetMapIter = g_OffsetMap.find(szFullPath);
	if (offsetMapIter != g_OffsetMap.end())
	{
		OffsetDefinition& offsetDefinition = (*offsetMapIter).second;
		*iOffset = offsetDefinition.m_iOffset;
		*pType = offsetDefinition.m_type;
		return true;
	}

    char szTempPath[2048];
    strcpy(szTempPath, szFullPath);
    char szClassName[1024];
    SplitPath(szFullPath, szClassName, szTempPath);
    *iOffset = 0;

    ServerClass* pCurrentServerClass = servergamedll->GetAllServerClasses();
    while (pCurrentServerClass)
    {
		if (strcmp(pCurrentServerClass->GetName(), szClassName) == 0)
        {
            if (GetPropOffsetInTable(pCurrentServerClass->m_pTable, szTempPath, iOffset, pType))
			{
				g_OffsetMap[szFullPath] = OffsetDefinition(*iOffset, *pType);
				return true;
			}
			return false;
        }
        pCurrentServerClass = pCurrentServerClass->m_pNext;
    }
    return false;
}

//---------------------------------------------------------------------------------
// Loops through a data table and prints out the property information, recursively
// if necessary.
//---------------------------------------------------------------------------------
void DumpServerClassProps(SendTable* pTable, int iTabLevel)
{
	if (iTabLevel > 16)
	{
		return;
	}

	static const char* szTabs = "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t";

	int iNumProps = pTable->GetNumProps();
	Msg(" [%d properties]:\n", iNumProps);
	for(int i=0; i < iNumProps; ++i)
	{
		char* szType;
		SendProp* pProp = pTable->GetProp(i);
		switch (pProp->GetType())
		{
		case DPT_Int:
			szType = "int";
			break;
		case DPT_Float:
			szType = "float";
			break;
		case DPT_Vector:
			szType = "vector";
			break;
		case DPT_VectorXY:
			szType = "vectorXY";
			break;
		case DPT_String:
			szType = "string";
			break;
		case DPT_Array:
			szType = "array";
			break;
		case DPT_DataTable:
			szType = "datatable";
			break;
		case DPT_Int64:
			szType = "int64";
			break;
		default:
			szType = "**Unknown**";
			break;
		}

		Msg("%*.*s%s %s (offset %d) ", iTabLevel, iTabLevel, szTabs, szType, pProp->GetName(), pProp->GetOffset());
		if (pProp->GetType() == DPT_DataTable && strcmp(pProp->GetName(), "baseclass") != 0)
		{
			DumpServerClassProps(pProp->GetDataTable(), iTabLevel + 1);
		}
		else
		{
			Msg("\n");
		}
	}
}

//---------------------------------------------------------------------------------
// Helpful function to dump all of the server classes and their respective
// properties.
//---------------------------------------------------------------------------------
void DumpServerClasses()
{
	SendTable* pSendTable = NULL;
	ServerClass* pCurrentServerClass = servergamedll->GetAllServerClasses();
	while (pCurrentServerClass)
	{
		Msg("%s %d", pCurrentServerClass->GetName(), pCurrentServerClass->m_InstanceBaselineIndex);
		DumpServerClassProps(pCurrentServerClass->m_pTable, 1);
		pCurrentServerClass = pCurrentServerClass->m_pNext;
	}
}

//---------------------------------------------------------------------------------
// This function exports methods relating to entity props
//---------------------------------------------------------------------------------
void Export_Props()
{
	// Functions
	BOOST_FUNCTION(DumpServerClasses, reference_existing_object_policy());
}
