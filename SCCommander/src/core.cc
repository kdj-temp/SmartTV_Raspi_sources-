/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * core.cc
 * Copyright (C) 2016 Narek Pahlevanyan <narek@ravcap.com>
 *
 */

#include "core.h"


Core::Core()
{
	mCryption = new Cryption(ENCRYPTION_KEY);
	mDataGetter = new DataGetter(NETWORK_INTERFACE);
	jReader = new Json::Reader();
	jWriter= new Json::StyledWriter();
	myState = INITIALIZING;
	mSConnector = new SConnector(AES_SECRET, POST_SECRET,API_LINK, mCryption, jWriter);

	std::string ** ndata = mDataGetter->getMACAndIP();
	
	mEventToServer = new Json::Value(Json::objectValue);   
   
     (*mEventToServer)["MAC"] = *(ndata[0]);
	 (*mEventToServer)["IP"] = *(ndata[1]);
	
	delete ndata[0];
	delete ndata[1];
	delete [] ndata;	

	//
	CommandSender::clearCommands();
}

Core::~Core()
{
	// delete classes...
	delete mCryption;
	delete mDataGetter;
	delete mSConnector;	
	delete jReader;
	delete jWriter;
}

void Core::processReply(std::string& pCryptedRequest)
{
	if (pCryptedRequest != "")
	{
		std::string decryptedReply = mCryption->decrypt(pCryptedRequest);

		// parse JSON...
		Json::Value jsonreply;   // will contains the root value after parsing.

		//printf("DEC = %s\n",decryptedReply.c_str());
		
		bool parsingSuccessful = jReader->parse( decryptedReply, jsonreply);
		if ( !parsingSuccessful )
		{
			// report to the user the failure and their locations in the document.
			throw "Failed to parse configuration\n" + 
				   jReader->getFormattedErrorMessages();
		} else {
			// start jam...
			// Get the value of the member of root named 'encoding', return 'UTF-8' if there is no
			// such member.
			
			int state = jsonreply.get("s", -1).asInt();

			switch(state) {
				case SYNCHING: {  
						   stateSync(jsonreply, pCryptedRequest);
						   break;
						} // scope of 'x' ends here
				case RESTARTING: {  
						   stateRestart();
						   break;
						} // scope of 'x' ends here
				case INTERNAL_REMOVE:
				{
					stateUnregister();
					break;
				}
				default:
					setDefaultState();
					//printf("No Action! state is = %d\n", state); // no error
						 break;
			}

		}	
	}
}

void Core::stateRestart()
{
	printf("Restarting!\n");
						   
	sync();
	reboot(RB_AUTOBOOT);
}

void Core::stateUnregister()
{
	CommandSender::stopPlaying(true);
	usleep(200);

	FileOP::removeFile(DATA_FILE_PATH);
		
	// delete existing videos!
	FileOP::deleteFolderContent(VIDDOWNLOAD_FOLDER_PATH);	
}


bool Core::readDataFile(std::string& pOutDecryptedJson)
{
	try
	{
		
		if (FileOP::fileExists(DATA_FILE_PATH))
		{
			// read file into std::string...
			FILE* f = fopen(DATA_FILE_PATH.c_str(), "r");

		   // Determine file size
		   fseek(f, 0, SEEK_END);
		   size_t size = ftell(f);

		   char* where = new char[size];
		   rewind(f);
		   fread(where, sizeof(char), size, f);
		   pOutDecryptedJson.assign(where);
			fclose(f);
		   delete[] where;
		   return true;
		}

		return false;
	} catch (...)
	{
		throw;
	}	
}


Json::Value * Core::getExistingVideos()
{
	Json::Value * videos = new Json::Value(Json::arrayValue);
	
	std::string decrData = "";

	// check if file exists...
	if (readDataFile(decrData)) {
		decrData = mCryption->decrypt(decrData);

		// parse JSON...
		Json::Value jsonreply;   // will contains the root value after parsing.
		Json::Value playlist(Json::arrayValue);
					
		bool parsingSuccessful = jReader->parse( decrData, jsonreply);
		if ( !parsingSuccessful )
		{
			// report to the user the failure and their locations in the document.
			throw "Failed to parse data.raw\n" + 
				   jReader->getFormattedErrorMessages();
		} else {
			// start jam...
			
				// decrypt and load into memory
				std::string ppSYNC = jsonreply["syncdata"].toStyledString();
				//printf("aa = %s\n",ppSYNC.c_str());
				bool parseToValue = jReader->parse(ppSYNC, playlist);

				ppSYNC = playlist[0]["Videos"].toStyledString();
				parseToValue = jReader->parse(ppSYNC, (*videos));
		}
	}
	return videos;
}

bool Core::itemExists(std::string& pItemToFind, std::string& pWhichTag, 
                      Json::Value* pJsonContainer)
{
	if (pItemToFind == "")
		throw "pItemToFind is empty!";

	if (0 == pJsonContainer) 
		throw "Json container can't be null!";
	
	for ( int vid = 0; vid < pJsonContainer->size(); ++vid )
		{
			std::string vfile = (*pJsonContainer)[vid].get(pWhichTag, "").asString();
			if (vfile == pItemToFind)
				return true;
		}

	return false;
}

void Core::stateSync(Json::Value &pDecrReply, std::string& pCryptedData)
{
	// 
	if (CommandSender::stopPlaying(true))
	{		
		usleep(1000);

		while(CommandSender::isYetPlaying())
		{
			usleep(1000000);
		}
		usleep(10000);
		
		// get existing vids...
		Json::Value * extvids = getExistingVideos ();

		/*for ( int vid = 0; vid < extvids->size(); ++vid )
		{
			// get the video filename
			std::string vfile = (*extvids)[vid].get("filename", "").asString();
			vfile = VIDDOWNLOAD_FOLDER_PATH + "/" + vfile;
			printf("YOPZA = %s\n", vfile.c_str());
		}

		
		return;
		*/
		
		// delete existing videos!
		//FileOP::deleteFolderContent(VIDDOWNLOAD_FOLDER_PATH);
	
		Json::Value playlists(Json::arrayValue);

		std::string ppSYNC = pDecrReply["syncdata"].toStyledString();
		bool parseToValue = jReader->parse(ppSYNC, playlists);
	
			for ( int index = 0; index < playlists.size(); ++index ){  // Iterates over the sequence elements.
				// get the videos...
				
				std::string pname = playlists[index].get("pname", "").asString();
				//printf("Playlist Name: %s\n", pname.c_str());
				
				Json::Value videos(Json::arrayValue);
					ppSYNC = playlists[index]["Videos"].toStyledString();
				
					parseToValue = jReader->parse(ppSYNC, videos);
					std::string tagName = "filename";
				
					for ( int vid = 0; vid < videos.size(); ++vid ){
							
							// get the video filename
							std::string vfile = videos[vid].get(tagName.c_str(), "").asString();

							printf("Processing video: %s\n", vfile.c_str());
						
							// check if video exists...
							if (vfile != "" && !itemExists(vfile, tagName, extvids)) { 
								std::string downloadfile = VIDDOWNLOAD_URL_PATH + vfile;
								std::string outputfile = VIDDOWNLOAD_FOLDER_PATH + "/" + vfile;
								if (mSConnector->downloadFile (downloadfile, outputfile))                   
									printf("Downloaded video: %s\n", vfile.c_str());
								else
									printf("Not able to download %s file\n",vfile.c_str());
							} else {
									printf("Video exists. Skipping \n");
							}
						}
					// remove existing not used videos!
					for ( int vid = 0; vid < extvids->size(); ++vid )
					{
						// get the video filename
						std::string vfile = (*extvids)[vid].get("filename", "").asString();

						if (vfile != "" && !itemExists(vfile, tagName, &videos)){
							// removing!!!!
							vfile = VIDDOWNLOAD_FOLDER_PATH + "/" + vfile;
							FileOP::removeFile(vfile);
						}
					}
					delete extvids;
				
				break; // we need only first...
				setNewStateWithSend(STAND_BY,false);
			}
		
		// let's create AES data file for usage in loopPlayer
		if (FileOP::removeFile(DATA_FILE_PATH)){
			
			//printf("AA = %s",pDecrReply);
			if (FileOP::createNewFile(DATA_FILE_PATH,pCryptedData)){
				
					// resume playing!
					// reload data file!!
					CommandSender::stopPlaying(false);
					usleep(5000);	
					
					CommandSender::reloadDataFile(true);
				
					setNewStateWithSend(STAND_BY,false);
			} else {
				throw "Can't create data.raw file!";
			}
		}
		
	} else {
		throw "Can't synchronize! Sending command failed!";
	}
}

void Core::setDefaultState()
{
	if (FileOP::fileExists (COMMAND_SEND_DIR_PATH+"/" + CMD_PLAYING_FILE))
	{
		setNewStateWithSend(PLAYING,false);	
	} else {
		setNewStateWithSend(STAND_BY,false);
	}
}

void Core::setNewStateWithSend(DSTATE pNewState, bool pSend)
{
	myState = pNewState;
	
	(*mEventToServer)["ms"] = myState;
	
	if (pSend){
		mSConnector->sendToApi(mEventToServer);
	}
}

void Core::start()
{	
	setNewStateWithSend(INITIALIZING,false);
	printf("SCCommander started - OK!\n");
	while(true)
	{
		(*mEventToServer)["FS"] = mDataGetter->getFreeSpaceInMb();		
		std::string serverReply = mSConnector->sendToApi(mEventToServer);
		//printf("Reply from API = %s\n\n\n", serverReply.c_str());
		// decrypted reply...
		processReply(serverReply);
		serverReply = "";
		//
		usleep(PING_WAIT_MICROSECONDS);
		//
	}
}

void finish();
