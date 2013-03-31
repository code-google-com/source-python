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

#include "usermessage.h"

CUserMessage::CUserMessage(const IRecipientFilter &recipient_filter, const char *message_name ) :
	CUserMessageImplementation(recipient_filter, message_name),
	m_sent(false)
{
	set_message_index();
}

CUserMessage::~CUserMessage()
{
	send_message();
}

void CUserMessage::send_message()
{
	if (m_sent == false)
	{
		send_message_internal();
		m_sent = true;
	}
}

bool CUserMessage::has_been_sent() const
{
	return m_sent;
}

const char * CUserMessage::get_message_name() const
{
	return m_message_name;
}

const int CUserMessage::get_message_index() const
{
	return m_message_index;
}

const IRecipientFilter & CUserMessage::get_recipient_filter() const
{
	return m_recipient_filter;
}