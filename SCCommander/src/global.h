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

static const std::string DATA_FILE_PATH = "./data.raw";
static const int PING_WAIT_MICROSECONDS = 30000000;
/////////////////////////////////////////////////////////

static const std::string NETWORK_INTERFACE = "wlan0";

static const std::string API_LINK = "http://67.227.156.25/adminpanel/index.php/handlerapi";
static const std::string VIDDOWNLOAD_URL_PATH = "http://67.227.156.25/adminpanel/uploads/";
static const std::string VIDDOWNLOAD_FOLDER_PATH = "./videos";
static const std::string COMMAND_SEND_DIR_PATH = "./cmds";

static const std::string ENCRYPTION_KEY = "n4r3kR3cU";
static const std::string POST_SECRET = "Po9109ui1";
static const std::string AES_SECRET = "4rm3nist4nNaR";

static inline std::string trim(std::string& str)
{
	str.erase(0, str.find_first_not_of(' '));       //prefixing spaces
	str.erase(str.find_last_not_of(' ')+1);         //surfixing spaces
	return str;
}


#endif // _DATA_GETTER_H_
