/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * LOGIC.h
 * Copyright (C) 2016 Narek Pahlevanyan <narek@ravcap.com>
 *
 * Logic of the program
 */

#ifndef _LOGIC_H_
#define _LOGIC_H_
#include <unistd.h>
#include <sys/reboot.h>
#include <fstream>

#include "global.h"
#include "json/json.h"
#include "cryption.h"
#include "file-op.h"
#include "command-sender.h"

class Logic
{
public:
	Logic();
	~Logic(); // destructor
	void start();
	void finish();
protected:

private:
	bool readDataFile(std::string&);
	bool retrieveVideoData(std::string&, 
	                       Json::Value&, 
	                       Json::Value&,
	                       time_t& pStartPlaylistTime,
	                   	   time_t& pEndPlaylistTime);
	
	void setDefaultState();
	bool isCorrectPlayingTime(time_t&, time_t&);
	void adjustDateTimeSetting(tm&, tm*);
	std::string getTimeComponent(const std::string&);
	
	DSTATE myState;
	
	Cryption* mCryption;
	Json::Reader* jReader;
	//Json::StyledWriter* jWriter;

};

#endif // _Logic_H_

