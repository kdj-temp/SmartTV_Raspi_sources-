/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * command-sender.cc
 * Copyright (C) 2016 Narek Pahlevanyan <narek@ravcap.com>
 */

#include "command-sender.h"

bool CommandSender::reloadDataFile(bool pFlag)
{
	std::string pStFile = COMMAND_SEND_DIR_PATH + "/" + CMD_RELOAD_DATA_FILE; 
	if (pFlag)
		return FileOP::createNewFile(pStFile,"");		
	else{
		return FileOP::removeFile(pStFile);
	}
}

bool CommandSender::stopPlaying(bool pFlag)
{
	std::string pStFile = COMMAND_SEND_DIR_PATH + "/" + CMD_STOP_FILE; 
	if (pFlag)
		return FileOP::createNewFile(pStFile,"");		
	else{
		FileOP::removeFile(COMMAND_SEND_DIR_PATH + "/" + CMD_PLAYING_FILE);
		return FileOP::removeFile(pStFile);
	}
}

bool CommandSender::clearCommands()
{
	return FileOP::deleteFolderContent(COMMAND_SEND_DIR_PATH);
}

bool CommandSender::isYetPlaying()
{
	return FileOP::fileExists (COMMAND_SEND_DIR_PATH + "/" + CMD_PLAYING_FILE);
}
