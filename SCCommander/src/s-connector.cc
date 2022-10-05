/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * s-connector.cc
 *
 */

#include "s-connector.h"


SConnector::SConnector(std::string pAesSecret,
                       std::string pPostSecret,
                       std::string pApiLink,
                       Cryption* pCrypto,
                       Json::StyledWriter* pJsWriter)
{	
	mAesSecret = pAesSecret;
	mPostSecret = pPostSecret;
	mAPILink = pApiLink;
	mJsWriter = pJsWriter;
	
	trim(mAPILink);

	if (mAPILink == "")
		throw "API link not provided!";

	if (0 == pCrypto)
		throw "Cryption class not provided!";

	mCrypto = pCrypto;
}


size_t SConnector::writeCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

size_t SConnector::write_to_file(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

bool SConnector::downloadFile(std::string pDownloadURL, std::string pSavePath)
{
	try
	{
		CURL *curl;
		FILE *fp;
		CURLcode res;
		//char outfilename[FILENAME_MAX] = "C:\\bbb.txt";
		curl = curl_easy_init();
		if (curl) {
		    fp = fopen(pSavePath.c_str(),"wb");
			if (fp == 0){
				throw "Can't create file for downloading! (maybe not enough privilegies ?)";				
			}
		    curl_easy_setopt(curl, CURLOPT_URL, pDownloadURL.c_str());
		    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_file);
		    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		    res = curl_easy_perform(curl);
		    /* always cleanup */
		    curl_easy_cleanup(curl);
		    fclose(fp);
		}

		return true;
	} catch(...){
		throw;
	}
}

std::string SConnector::sendToApi(Json::Value*pDataToSend)
{
	CURL *curl;
	CURLcode res;
	std::string readBuffer;

    curl = curl_easy_init();

	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, mAPILink.c_str());
		curl_easy_setopt(curl, CURLOPT_POST, 1);
	  
	  /* Now specify the POST data */ 

		(*pDataToSend)["sec"] = mAesSecret;

	  std::string NotcryptedData = mJsWriter->write( *pDataToSend );
	  std::string cryptData = mCrypto->crypt(NotcryptedData);

		char *output = curl_easy_escape(curl, cryptData.c_str(), cryptData.length());
	  	cryptData.assign(output);
	  
		 cryptData= "s=" + mPostSecret +"&d="+cryptData;
		 curl_easy_setopt(curl, CURLOPT_POSTFIELDS, cryptData.c_str());
    	 curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
	  	 curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
	  
    res = curl_easy_perform(curl);
	  
    curl_easy_cleanup(curl);

  }

	// server reply
    return readBuffer;
}

