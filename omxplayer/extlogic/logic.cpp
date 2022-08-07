/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * logic.cc
 * Copyright (C) 2016 Narek Pahlevanyan <narek@ravcap.com>
 *
 */

#include "logic.h"
std::string Logic::getVideoFilePath()
{
	return mVideoFile;
}

bool Logic::canPlay()
{	
	CommandSender::setPlaying(false);
	
	if (!getVideoFilePath().empty() && 
	    !CommandSender::getStopAllplaying() && 
	    CommandSender::isAllowedToPlay())
	{
		CommandSender::setPlaying(true);
		//printf("PLAYING!! - %s", mVideoFile.c_str());
		//fflush(stdout);
		//sleep(15);
		return true;		
	}
	return false;
}

Logic::~Logic()
{
	CommandSender::setPlaying(false);	
}

Logic::Logic(int argc, char* argv[])
{
	//printf("ALLO\n");
	if (argc > 2)
		mVideoFile.assign(argv[3]);
	else
		throw "Video file not provided!";

	//printf("setted file is %s",mVideoFile.c_str());

}

