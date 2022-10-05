/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * s-connector.h
 *
 */

#ifndef _S_CONNECTOR_H_
#define _S_CONNECTOR_H_

#include <string>
#include <cstring>
#include <stdio.h>
#include <curl/curl.h>
#include "global.h"
#include "cryption.h"

using std::string;

class SConnector
{
public:
	SConnector(std::string,
	           std::string,
	           std::string,
	           Cryption*,
	           Json::StyledWriter*);
	
	std::string sendToApi(Json::Value*);
	bool downloadFile(std::string pDownloadURL, std::string pSavePath);
protected:

private:
	static size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp);
	static size_t write_to_file(void *ptr, size_t size, size_t nmemb, FILE *stream);
	
	string mAesSecret;
	string mPostSecret;
	string mAPILink;	
	Cryption * mCrypto;	
	Json::StyledWriter* mJsWriter;
};

#endif // _S_CONNECTOR_H_

