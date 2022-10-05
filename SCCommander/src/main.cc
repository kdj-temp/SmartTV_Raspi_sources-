/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.cc
 * Copyright (C) 2016 Narek Pahlevanyan <narek@ravcap.com>
 * 
 */

#include <iostream>
#include "core.h"


int main()
{

//sleeeep...
sleep(20);
	try{

		Core * coreobj = new Core();
		coreobj->start ();

		delete coreobj;
	} catch(char const *e){
		printf("Error occured - %s ",e);
	}
	return 0;
}

