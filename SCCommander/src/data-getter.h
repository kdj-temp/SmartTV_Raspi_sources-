/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * data-getter.h
 * Copyright (C) 2016 Narek Pahlevanyan <narek@ravcap.com>

 */

#ifndef _DATA_GETTER_H_
#define _DATA_GETTER_H_

#include <string>
#include <cstring>
#include <sys/ioctl.h>
#include <net/if.h> 
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h> /* struct hostent, gethostbyname */
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include "global.h"

using std::string;

class DataGetter
{
public:	
	DataGetter(std::string);
	~DataGetter();
	string** getMACAndIP();
	double getFreeSpaceInMb();
	
protected:

private:
	int get_int64_value_from_ascii_string (string source_string, int char_index, int64_t *result);
	string do_console_command_get_result (char* command);
	string * mInterfaceName;

};

#endif // _DATA_GETTER_H_

