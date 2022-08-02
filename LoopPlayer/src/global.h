/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * global.h
 * Copyright (C) 2016 Narek Pahlevanyan <narek@ravcap.com>

 */

#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
#include <unistd.h>

#include "json/json.h"

enum DSTATE 
{ 
	NOT_STARTED = 0,
	PLAYING = 1,
	SYNCHING = 2,
	RESTARTING = 3,
	INITIALIZING = 4,
	STAND_BY = 5,
	INTERNAL_REMOVE = -999
};

/////////////////////////////////////////////////////////
static const std::string CMD_STOP_FILE = "stopplayingall";
static const std::string CMD_PLAYING_FILE = "isplaying";
static const std::string CMD_RELOAD_DATA_FILE = "reloaddatafile";
static const std::string CMD_ALLOW_PLAYER = "allowplayer";

static const std::string DATA_FILE_PATH = "./data.raw";
static const int WAIT_MICROSECONDS = 5000000; //  5 seconds
static const int WAIT_TILL_PLAYER_GETS_FREE = 2000000; //  2 seconds

/////////////////////////////////////////////////////////

static const std::string VIDDOWNLOAD_FOLDER_PATH = "./videos";
static const std::string COMMAND_SEND_DIR_PATH = "./cmds";

static const std::string ENCRYPTION_KEY = "n4r3kR3cU";
static const std::string AES_SECRET = "4rm3nist4nNaR";

static const int DAY_SECONDS = 86400;

static inline std::string trim(std::string& str)
{
	str.erase(0, str.find_first_not_of(' '));       //prefixing spaces
	str.erase(str.find_last_not_of(' ')+1);         //surfixing spaces
	return str;
}


#endif // _DATA_GETTER_H_
