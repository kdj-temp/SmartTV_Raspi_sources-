/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * data-getter.cc
 * Copyright (C) 2016 Narek Pahlevanyan <narek@ravcap.com>
 *
 */

#include "data-getter.h"

DataGetter::DataGetter(std::string pInterfaceName)
{
	mInterfaceName = new string(pInterfaceName);
	
	trim(*mInterfaceName);
	
	if (*mInterfaceName == "")
		throw "Network interface not provided!";	
}

DataGetter::~DataGetter()
{
	delete mInterfaceName;
}

double DataGetter::getFreeSpaceInMb()
{
	int64_t free_disk_space;
	get_int64_value_from_ascii_string(do_console_command_get_result((char*)"df -k /tmp | tail -1 | awk '{print $4}'"), 0, &free_disk_space); //Get free space in kB

	return free_disk_space/1000.0;
}

int DataGetter::get_int64_value_from_ascii_string (string source_string, int char_index, int64_t *result)
{
	int32_t value = -1;
	int32_t value_last = 0;
	char *p_source_string;
	
	
	p_source_string = (char*)source_string.c_str();
	p_source_string += char_index;

	//Ignore any leading spaces
	while (*p_source_string == ' ')
		p_source_string++;

	while ((*p_source_string >= '0') && (*p_source_string <= '9'))
	{
		if (value < 0)
			value = 0;
		value_last = value;

		value *= 10;
		value += (*p_source_string++ - 0x30);

		if (value_last > value)
		{
			value = -1;				//Value is > max possible
			break;
		}
	}
	*result = value;
	return((int)(p_source_string - (char*)source_string.c_str()));
}

string DataGetter::do_console_command_get_result (char* command)
{
	FILE* pipe = popen(command, "r");
	if (!pipe)
		return "ERROR";
	
	char buffer[128];
	string result = "";
	while(!feof(pipe))
	{
		if(fgets(buffer, 128, pipe) != NULL)
			result += buffer;
	}
	pclose(pipe);
	return(result);
}

string** DataGetter::getMACAndIP()
{
	int fd;
    struct ifreq ifr;
    //char *iface = "eth0";
    unsigned char *mac = NULL;
	char macFormatted[19];
	
	std::string** outData = new string*[2];

	outData[0] = new std::string();
	outData[1] = new std::string();
		
    std::memset(&ifr, 0, sizeof(ifr));

    fd = socket(AF_INET, SOCK_DGRAM, 0);

    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name , mInterfaceName->c_str() , IFNAMSIZ-1);

	// mac
    if (0 == ioctl(fd, SIOCGIFHWADDR, &ifr)) {
        mac = (unsigned char *)ifr.ifr_hwaddr.sa_data;

        //display mac address
        sprintf(macFormatted, "%.2X:%.2X:%.2X:%.2X:%.2X:%.2X" , mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

		outData[0]->assign(macFormatted);
	}

	// ip
	if (0 == ioctl(fd, SIOCGIFADDR, &ifr)) {
		char * IP[50];
		outData[1]->assign(inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
	}
	
    close(fd);

	return outData;
}

