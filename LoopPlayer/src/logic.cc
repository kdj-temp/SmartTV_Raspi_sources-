/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * Logic.cc
 * Copyright (C) 2016 Narek Pahlevanyan <narek@ravcap.com>
 *
 */

#include "logic.h"


Logic::Logic()
{
	mCryption = new Cryption(ENCRYPTION_KEY);
	jReader = new Json::Reader();
	myState = INITIALIZING;

	CommandSender::AllowPlay(false);
}

Logic::~Logic()
{
	// delete classes...
	delete mCryption;
	delete jReader;
	//delete jWriter;
}

bool Logic::readDataFile(std::string& pOutDecryptedJson)
{
	try
	{
		pOutDecryptedJson = "";
		if (FileOP::fileExists(DATA_FILE_PATH))
		{
			/*printf("start sleep/n");
			printf("a");
			sleep(20);
			
			// read file into std::string...
			FILE* f = fopen(DATA_FILE_PATH.c_str(), "r");

		   // Determine file size
		   fseek(f, 0, SEEK_END);
		   size_t size = ftell(f);

		   char* where = new char[size];
		   rewind(f);
		   fread(where, sizeof(char), size, f);
		   pOutDecryptedJson = std::string(where);
			fclose(f);
		   delete[] where;
			
			*/

			std::fstream f(DATA_FILE_PATH.c_str(), std::fstream::in);
			getline( f, pOutDecryptedJson, '\0');
			//printf("I FILE IS OK lssine was %s\n",pOutDecryptedJson.c_str() );
			f.close();
			
		   return true;
		}

		return false;
	} catch (...)
	{
		throw;
	}	
}

std::string Logic::getTimeComponent (const std::string& pFullLine)
{
				std::size_t pFndIndex = pFullLine.find(" ");
				if (pFndIndex!=std::string::npos) {
					return pFullLine.substr(pFndIndex+1);
				}
	return "";
}

void Logic::adjustDateTimeSetting(tm& pAdjustThisDateTime, tm* pAdjustToMeDateTime)
{
	pAdjustThisDateTime.tm_year = pAdjustToMeDateTime->tm_year;
	pAdjustThisDateTime.tm_mon = pAdjustToMeDateTime->tm_mon;
	pAdjustThisDateTime.tm_mday = pAdjustToMeDateTime->tm_mday;
	pAdjustThisDateTime.tm_isdst = 0; 
}

bool Logic::retrieveVideoData(std::string& pCryptedData, 
                              Json::Value& playlist, 
                              Json::Value& videos,
                              time_t& pStartPlaylistTime,
	                   		  time_t& pEndPlaylistTime)
{
	try
	{

		std::string decryptedReply = mCryption->decrypt(pCryptedData);

		// parse JSON...
		Json::Value jsonreply;   // will contains the root value after parsing.

		bool parsingSuccessful = jReader->parse( decryptedReply, jsonreply);
		if ( !parsingSuccessful )
		{
			// report to the user the failure and their locations in the document.
			throw "Failed to parse data.raw\n" + 
				   jReader->getFormattedErrorMessages();
		} else {
			// start jam...
			int state = jsonreply.get("s", -1).asInt();

			if (state == SYNCHING){
				
				// decrypt and load into memory
				std::string ppSYNC = jsonreply["syncdata"].toStyledString();
				//printf("aa = %s\n",ppSYNC.c_str());
				bool parseToValue = jReader->parse(ppSYNC, playlist);

				ppSYNC = playlist[0]["Videos"].toStyledString();
				parseToValue = jReader->parse(ppSYNC, videos);

				// get times now...
				std::string timevalstart = playlist[0].get("startest", "").asString();
				std::string timevalend = playlist[0].get("endest", "").asString();
				
				timevalstart = getTimeComponent (timevalstart);
				timevalend = getTimeComponent (timevalend);

				//printf("S = %s\n",timevalstart.c_str());
				//printf("E = %s\n",timevalend.c_str());
				
				// get time..
				struct tm tms;
				struct tm tme;

				time_t theTime = time(NULL);
				struct tm *aTime = localtime(&theTime);
				
				strptime(timevalstart.c_str(), "%H:%M:%S", &tms);
				adjustDateTimeSetting(tms,aTime);
				
				//tms.tm_year = aTime->tm_year;
				//tms.tm_mon = aTime->tm_mon;
				//tms.tm_mday = aTime->tm_mday;
				//tms.tm_isdst = 0; 
				
				pStartPlaylistTime = mktime(&tms);  


				time_t theTime2 = time(NULL);
				struct tm *aTime2 = localtime(&theTime2);

				strptime(timevalend.c_str(), "%H:%M:%S", &tme);
				
				adjustDateTimeSetting(tme, aTime2);

				/*
				tme.tm_year = aTime2->tm_year;
				tme.tm_mon = aTime2->tm_mon;
				tme.tm_mday = aTime2->tm_mday;
				tme.tm_isdst = 0; 
				*/
				
				pEndPlaylistTime = mktime(&tme);
				
				// check for next day to finish:
				// this is the case where start time is > end time 
				if (difftime(pStartPlaylistTime,pEndPlaylistTime) >= 0.0) {
					pEndPlaylistTime += DAY_SECONDS;
				}
				
					//printf ( "START t: %s", ctime (&pStartPlaylistTime) );
					//printf ( "End t: %s", ctime (&pEndPlaylistTime) );

				return parseToValue;
			}
		}
		
		return false;
	} catch (...)
	{
		throw;
	}	
}

bool Logic::isCorrectPlayingTime(time_t& starttime, time_t& endtime)
{
	time_t currentTime = time(NULL);

	//printf ( "END vid time: %s", ctime (&endtime) );
	// adjust date component if needed...
	double diffstart = difftime(currentTime,starttime);
	while (diffstart >= DAY_SECONDS) {
		starttime += DAY_SECONDS;
		endtime += DAY_SECONDS;
		diffstart = difftime(currentTime,starttime);
	}
	
	return (diffstart >= 0.0 && difftime(currentTime,endtime) <= 0.0);
	
}

void Logic::setDefaultState()
{
	return;
	if (FileOP::fileExists (COMMAND_SEND_DIR_PATH+"/" + CMD_PLAYING_FILE))
	{
		//setNewStateWithSend(PLAYING,false);	
	} else {
		//setNewStateWithSend(STAND_BY,false);
	}
}



void Logic::start()
{	
	printf("Loop part started - OK!\n");
	while(true)
	{
		// check if data file exists...
		std::string encjson = "";
		CommandSender::AllowPlay(false);

		CommandSender::reloadDataFile(false); //we reloading right now!

		if (!CommandSender::getStopAllplaying() && readDataFile (encjson))
		{
			Json::Value playlists(Json::arrayValue);
			Json::Value videos(Json::arrayValue);
			time_t startTime, endTime;
			
			if (retrieveVideoData (encjson,playlists, videos, startTime, endTime))
			{
				bool finishPlaying = false;
				while (!finishPlaying)
				{
					if (CommandSender::getStopAllplaying() || CommandSender::shouldReloadDataFile ())
						finishPlaying = true;
								
					// check if times are correct...
					if (isCorrectPlayingTime(startTime, endTime))
					{
						// print video names...
						for ( int vid = 0; vid < videos.size(); ++vid )
						{
							if (!isCorrectPlayingTime(startTime, endTime))
								break;
								
							if (!CommandSender::getStopAllplaying() || CommandSender::shouldReloadDataFile())
							{
								// get the video filename
									std::string vfile = videos[vid].get("filename", "").asString();
									std::string vstart = videos[vid].get("starttime", "0.0").asString();
									
								
								vfile = VIDDOWNLOAD_FOLDER_PATH + "/" + vfile;
								
								//printf("Pushing video to player : %s\n", vfile.c_str());

									CommandSender::AllowPlay(true);

									// send to player!!!
									while (CommandSender::isYetPlaying())
									{
										usleep(WAIT_TILL_PLAYER_GETS_FREE);
									}
									// send to player!!!!!!!
									vfile = "./player -l " + vstart + " -o hdmi " + vfile;
									system(vfile.c_str());			
									////////////////////////////////
									// wait until playing finishes!!
									usleep(WAIT_MICROSECONDS/8);
							} else {
								finishPlaying = true;
								break;
							}
						}
						CommandSender::AllowPlay(false);
					}
					usleep(WAIT_MICROSECONDS/4);
				}
			}
		}
		usleep(WAIT_MICROSECONDS);
		//
	}
}
