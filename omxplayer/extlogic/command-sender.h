/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * command-sender.h
 * Copyright (C) 2016 Narek Pahlevanyan <narek@ravcap.com>
 *
 */

#ifndef _COMMAND_SENDER_H_
#define _COMMAND_SENDER_H_

#include <string>
#include "global.h"
#include "file-op.h"

class CommandSender
{
public:
	// stops Player
	static bool setPlaying(bool);
	static bool getStopAllplaying();
	static bool isAllowedToPlay();
protected:

private:

};

#endif // _COMMAND_SENDER_H_

