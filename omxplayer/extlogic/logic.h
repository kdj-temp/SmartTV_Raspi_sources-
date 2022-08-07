/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * logic.h
 * Copyright (C) 2016 Narek Pahlevanyan <narek@ravcap.com>
 *
 */

#ifndef _LOGIC_H_
#define _LOGIC_H_

#include <string>
#include "global.h"
#include "command-sender.h"

class Logic
{
public:
	Logic(int, char* argv[]);
	std::string getVideoFilePath();
	bool canPlay();
	~Logic();
protected:

private:
	std::string mVideoFile;
};

#endif // _LOGIC_H_

