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

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "cvar_wrap.h"

//-----------------------------------------------------------------------------
// CConVar constructors.
//-----------------------------------------------------------------------------
CConVar::CConVar( ConVar* pConVar )
{
	m_Name = pConVar->GetName();
}

CConVar::CConVar( const char *pName )
{
	ConVar *convar = cvar->FindVar(pName);
	if( !convar )
	{
		ConVar *convar = new ConVar(pName, "0", 0);
	}

	m_Name = pName;
}

CConVar::CConVar( const char *pName, const char *pDefaultValue, int flags )
{
	ConVar *convar = cvar->FindVar(pName);
	if( !convar )
	{
		ConVar *convar = new ConVar(pName, pDefaultValue, flags);
	}

	m_Name = pName;
}

CConVar::CConVar( const char *pName, const char *pDefaultValue,
		int flags, const char *pHelpString )
{
	ConVar *convar = cvar->FindVar(pName);
	if( !convar )
	{
		ConVar *convar = new ConVar(pName, pDefaultValue, flags, strdup(pHelpString));
	}

	m_Name = pName;
}

CConVar::CConVar( const char *pName, const char *pDefaultValue, int flags,
		const char *pHelpString, bool bMin, float fMin, bool bMax, float fMax )
{
	ConVar *convar = cvar->FindVar(pName);
	if( !convar )
	{
		ConVar *convar = new ConVar(pName, pDefaultValue, flags,
			strdup(pHelpString), bMin, fMin, bMax, fMax);
	}

	m_Name = pName;
}

//-----------------------------------------------------------------------------
// CConVar methods.
//-----------------------------------------------------------------------------
const char* CConVar::get_help_text()
{
	ConVar *convar = cvar->FindVar(m_Name);
	return convar->GetHelpText();
}

const char *CConVar::get_name()
{
	ConVar *convar = cvar->FindVar(m_Name);
	return convar->GetName();
}

bool CConVar::is_flag_set( int iFlag )
{
	ConVar *convar = cvar->FindVar(m_Name);
	return convar->IsFlagSet(iFlag);
}

void CConVar::add_flags( int iFlags )
{
	ConVar *convar = cvar->FindVar(m_Name);
	convar->AddFlags(iFlags);
}

int CConVar::get_flags()
{
	ConVar *convar = cvar->FindVar(m_Name);
	return convar->GetFlags();
}

bool CConVar::is_command()
{
	ConVar *convar = cvar->FindVar(m_Name);
	return convar->IsCommand();
}

float CConVar::get_float()
{
	ConVar *convar = cvar->FindVar(m_Name);
	return convar->GetFloat();
}

int CConVar::get_int()
{
	ConVar *convar = cvar->FindVar(m_Name);
	return convar->GetInt();
}

bool CConVar::get_bool()
{
	ConVar *convar = cvar->FindVar(m_Name);
	return convar->GetBool();
}

char const *CConVar::get_string()
{
	ConVar *convar = cvar->FindVar(m_Name);
	return convar->GetString();
}

void CConVar::set_float( float flValue )
{
	ConVar *convar = cvar->FindVar(m_Name);
	convar->SetValue(flValue);
}

void CConVar::set_int( int iValue )
{
	ConVar *convar = cvar->FindVar(m_Name);
	convar->SetValue(iValue);
}

void CConVar::set_bool( bool bValue )
{
	ConVar *convar = cvar->FindVar(m_Name);
	convar->SetValue(bValue);
}

void CConVar::set_string( const char *szValue )
{
	ConVar *convar = cvar->FindVar(m_Name);
	convar->SetValue(szValue);
}

void CConVar::revert()
{
	ConVar *convar = cvar->FindVar(m_Name);
	convar->Revert();
}

const char *CConVar::get_default()
{
	ConVar *convar = cvar->FindVar(m_Name);
	return convar->GetDefault();
}

/*
bool CConVar::has_min()
{
	ConVar *convar = cvar->FindVar(m_Name);
	return convar->HasMin();
}

bool CConVar::has_max()
{
	ConVar *convar = cvar->FindVar(m_Name);
	return convar->HasMax();
}

float CConVar::get_min_value()
{
	ConVar *convar = cvar->FindVar(m_Name);
	return convar->GetMinValue();
}

float CConVar::get_max_value()
{
	ConVar *convar = cvar->FindVar(m_Name);
	return convar->GetMaxValue();
}
*/

//-----------------------------------------------------------------------------
// CConCommandBase constructors.
//-----------------------------------------------------------------------------
CConCommandBase::CConCommandBase( const char *pName,
	const char *pHelpString, int flags )
{
	ConCommandBase *command = cvar->FindCommandBase(pName);
	if( !command )
	{
		ConCommandBase *command = new ConCommandBase(pName, strdup(pHelpString), flags);
	}

	m_ConCommandBase_ptr = command;
}

CConCommandBase::CConCommandBase( ConCommandBase* pConCommandBase )
{
	m_ConCommandBase_ptr = pConCommandBase;
}

//-----------------------------------------------------------------------------
// CConCommandBase methods.
//-----------------------------------------------------------------------------
bool CConCommandBase::is_command()
{
	return m_ConCommandBase_ptr->IsCommand();
}

bool CConCommandBase::is_registered()
{
	return m_ConCommandBase_ptr->IsRegistered();
}

bool CConCommandBase::is_flag_set( int iFlag )
{
	return m_ConCommandBase_ptr->IsFlagSet(iFlag);
}

void CConCommandBase::add_flags( int iFlags )
{
	m_ConCommandBase_ptr->AddFlags(iFlags);
}

void CConCommandBase::remove_flags( int iFlags )
{
	m_ConCommandBase_ptr->RemoveFlags(iFlags);
}

int CConCommandBase::get_flags()
{
	return m_ConCommandBase_ptr->GetFlags();
}

const char *CConCommandBase::get_name()
{
	return m_ConCommandBase_ptr->GetName();
}

const char *CConCommandBase::get_help_text()
{
	return m_ConCommandBase_ptr->GetHelpText();
}

ConCommandBase* CConCommandBase::get_pointer()
{
	return m_ConCommandBase_ptr;
}

//-----------------------------------------------------------------------------
// CServerCommand constructors.
//-----------------------------------------------------------------------------
CServerCommand::CServerCommand()
{
	m_CCommand_ptr = NULL;
}

CServerCommand::CServerCommand( CCommand* command )
{
	m_CCommand_ptr = command;
}

//-----------------------------------------------------------------------------
// CServerCommand methods.
//-----------------------------------------------------------------------------
int CServerCommand::get_arg_count()
{
	return m_CCommand_ptr->ArgC();
}

const char *CServerCommand::get_arg_string()
{
	return m_CCommand_ptr->ArgS();
}

const char *CServerCommand::get_command_string()
{
	return m_CCommand_ptr->GetCommandString();
}

const char *CServerCommand::get_arg( int iIndex )
{
	return m_CCommand_ptr->Arg(iIndex);
}

//-----------------------------------------------------------------------------
// CCvar methods.
//-----------------------------------------------------------------------------
void CCvar::register_con_command( CConCommandBase *pCommandBase )
{
	cvar->RegisterConCommand(pCommandBase->get_pointer());
}

void CCvar::unregister_con_command( CConCommandBase *pCommandBase )
{
	cvar->UnregisterConCommand(pCommandBase->get_pointer());
}

CConCommandBase *CCvar::find_command_base( const char *szName )
{
	ConCommandBase *pCommandBase = cvar->FindCommandBase(szName);
	if( !pCommandBase )
	{
		return NULL;
	}

	CConCommandBase *nCommandBase = new CConCommandBase(pCommandBase);
	return nCommandBase;
}

CConVar *CCvar::find_var( const char *szName )
{
	ConVar *pConVar = cvar->FindVar(szName);
	if( !pConVar )
	{
		return NULL;
	}

	CConVar *nConVar = new CConVar(pConVar);
	return nConVar;
}
