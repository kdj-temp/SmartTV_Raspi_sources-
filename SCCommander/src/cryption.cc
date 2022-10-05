/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * cryption.cc
 * Copyright (C) 2016 Narek Pahlevanyan <narek@ravcap.com>
 */

#include "cryption.h"


Cryption::Cryption(std::string pEncryptKey)
{
	trim(pEncryptKey);

	if (pEncryptKey == "")
		throw "Encryption key is not provided!";
		
	mEncryptKey = pEncryptKey + mbase64.base64_decode("cmFzcGkxOA==");
	
	mRijndael.MakeKey(mEncryptKey.c_str(), "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 16, 16);
}

std::string Cryption::crypt(std::string pStringToCrypt)
{
		int addPadding = 0;

		long SendLength = pStringToCrypt.length();
		while (true){
			if (SendLength%16==0)
				break;
			SendLength++;
		}
		addPadding = SendLength - pStringToCrypt.length();

		// add padding
		for(int i=1;i<=addPadding;i++){
			pStringToCrypt = " " + pStringToCrypt;		
		}

		char * szDataIn = new char[pStringToCrypt.length()+1]();
		std::fill(szDataIn, szDataIn + pStringToCrypt.length(), '\0');
	
			mRijndael.Encrypt(pStringToCrypt.c_str(), szDataIn, pStringToCrypt.length(), CRijndael::ECB);

			std::string encoded = mbase64.base64_encode(reinterpret_cast<const unsigned char*>(szDataIn),pStringToCrypt.length());

	delete [] szDataIn;
	
	return encoded;
}

std::string Cryption::decrypt(std::string pStringToDeCrypt)
{
	
	std::string decoded = mbase64.base64_decode(pStringToDeCrypt);

	//printf("deco=%s\n", decoded.c_str());

	char * szDataIn = new char[decoded.length()+1]();
	std::fill(szDataIn, szDataIn + decoded.length(), '\0');
	
	mRijndael.Decrypt(decoded.c_str(), szDataIn, decoded.length(), CRijndael::ECB);

	std::string decString(szDataIn);
		
	delete [] szDataIn;
	trim(decString);
	
	return decString;	
}
