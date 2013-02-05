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

#ifndef _USERMESSAGE_H_
#define _USERMESSAGE_H_

#include "irecipientfilter.h"

#include "../../../utility/wrap_macros.h"

#include GAME_INCLUDE_PATH(usermessage_implementation.h)

class CUserMessage : public CUserMessageImplementation
{
public:
	CUserMessage(const IRecipientFilter &recipient_filter, const char *message_name);
	~CUserMessage();

	virtual void send_message();

	const char *get_message_name() const;
	const int get_message_index() const;
	const IRecipientFilter &get_recipient_filter() const;
	bool has_been_sent() const;

private:
	bool m_sent;
};

#endif