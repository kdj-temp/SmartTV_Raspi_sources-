/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * cryption.h
 * Copyright (C) 2016 Narek Pahlevanyan <narek@ravcap.com>
 */

#ifndef _CRYPTION_H_
#define _CRYPTION_H_

#include <string>
#include <cstring>
#include <stdio.h>
#include "Rijndael.h"
#include "base64.h"
#include "global.h"

using std::string;

class Cryption
{
public:
	Cryption(std::string);
	std::string crypt(std::string);
	std::string decrypt(std::string);
	
protected:

private:
	CRijndael mRijndael;
	base64 mbase64;
	
	string mEncryptKey;		
};

#endif // _CRYPTION_H_

