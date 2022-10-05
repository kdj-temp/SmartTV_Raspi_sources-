/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * server.h
 * Copyright (C) 2016 Narek Pahlevanyan <narek@ravcap.com>

 */

#ifndef _SERVERIO_H_
#define _SERVERIO_H_

#include <string>

class serverio
{
public:
	serverio(std::string, int);
	std::string send();
protected:

private:
	std::string mHostURL;
	int mHostPort;
};

#endif // _SERVERIO_H_

