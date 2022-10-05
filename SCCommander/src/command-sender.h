/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * command-sender.h
 * Copyright (C) 2016 Narek Pahlevanyan <narek@ravcap.com>
 *
 * SCCommander is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * SCCommander is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _COMMAND_SENDER_H_
#define _COMMAND_SENDER_H_

#include <string>
#include "global.h"
#include "file-op.h"

class CommandSender
{
public:
	// stops loopPlayer and Player
	static bool stopPlaying(bool);
	static bool reloadDataFile(bool);
	
	static bool clearCommands();
	static bool isYetPlaying();
	
protected:

private:

};

#endif // _COMMAND_SENDER_H_

