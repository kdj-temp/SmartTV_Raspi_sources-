/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.cc
 * Copyright (C) 2016 Narek Pahlevanyan <narek@ravcap.com>
 * 
 */

#include <iostream>
#include "logic.h"

int main()
{
sleep(15);
printf("LP started\n");

	try{

		Logic * coreobj = new Logic();
		coreobj->start ();

		delete coreobj;
	} catch(char const *e){
		printf("Error occured in LoopPlayer - %s ",e);
	}
	return 0;
}

