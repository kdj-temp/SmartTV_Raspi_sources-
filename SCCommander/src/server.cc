/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * server.cc
 * Copyright (C) 2016 Narek Pahlevanyan <narek@ravcap.com>
 *
 
 */

#include "server.h"


serverio::serverio(std::string pHostName, int pPort)
{
	mHostURL = pHostName;
	if (mHostURL == "")
		throw "API link not provided!";
	
	mHostPort = pPort;
}

std::string serverio::send(std::string pDataToSend)
{
	
	
}


