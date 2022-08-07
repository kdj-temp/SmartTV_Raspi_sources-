/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * command-sender.cc
 * Copyright (C) 2016 Narek Pahlevanyan <narek@ravcap.com>
 */

#include "command-sender.h"


bool CommandSender::setPlaying(bool pFlag)
{
	std::string pStFile = COMMAND_SEND_DIR_PATH + "/" + CMD_PLAYING_FILE; 
	if (pFlag)
		return FileOP::createNewFile(pStFile,"");		
	else{
		return FileOP::removeFile(pStFile);
	}
}

bool CommandSender::getStopAllplaying()
{
	return FileOP::fileExists (COMMAND_SEND_DIR_PATH + "/" + CMD_STOP_FILE);
}

bool CommandSender::isAllowedToPlay()
{
	return FileOP::fileExists (COMMAND_SEND_DIR_PATH + "/" + CMD_ALLOW_PLAYER);
}
