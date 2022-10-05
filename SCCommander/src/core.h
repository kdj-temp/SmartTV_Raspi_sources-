/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * core.h
 * Copyright (C) 2016 Narek Pahlevanyan <narek@ravcap.com>
 *
 * Logic of the program
 */

#ifndef _CORE_H_
#define _CORE_H_
#include <unistd.h>
#include <sys/reboot.h>
#include <vector>
#include "global.h"
#include "json/json.h"
#include "cryption.h"
#include "data-getter.h"
#include "s-connector.h"
#include "file-op.h"
#include "command-sender.h"

class Core
{
public:
	Core();
	~Core(); // destructor
	void start();
	void finish();
protected:

private:
	
	void setNewStateWithSend(DSTATE, bool);
	void processReply(std::string&);
	void stateSync(Json::Value&, std::string&);
	void stateRestart();
	void stateUnregister();
	void setDefaultState();

	bool itemExists(std::string&, std::string&, Json::Value*);
	bool readDataFile(std::string&);
	Json::Value * getExistingVideos();
	
	DSTATE myState;
	DataGetter* mDataGetter;
	SConnector* mSConnector;
	Cryption* mCryption;
	Json::Reader* jReader;
	Json::StyledWriter* jWriter;

	Json::Value * mEventToServer;
	
};

#endif // _CORE_H_

