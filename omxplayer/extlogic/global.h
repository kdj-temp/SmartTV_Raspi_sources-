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


/////////////////////////////////////////////////////////
static const std::string CMD_STOP_FILE = "stopplayingall";
static const std::string CMD_PLAYING_FILE = "isplaying";
static const std::string CMD_ALLOW_PLAYER = "allowplayer";

static const int WAIT_MICROSECONDS = 5000000; //  5 seconds
static const int WAIT_TILL_PLAYER_GETS_FREE = 2000000; //  2 seconds

/////////////////////////////////////////////////////////

static const std::string COMMAND_SEND_DIR_PATH = "./cmds";

#endif // _DATA_GETTER_H_
