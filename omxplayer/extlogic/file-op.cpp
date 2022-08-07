/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * file-op.cc
 *
 */

#include "file-op.h"

bool FileOP::fileExists (const std::string& pFilePath)
{	
  struct stat buffer;   
  return (stat (pFilePath.c_str(), &buffer) == 0);
}

bool FileOP::removeFile(const std::string& pFilePath)
{
	try
	{
		if (fileExists(pFilePath))
			remove(pFilePath.c_str());
		return true;			
	} catch(...)
	{
		throw "Error removing file.";
	}	
}

bool FileOP::createNewFile(const std::string& pFilePath, const std::string& pContent)
{
	try
	{
		const char * fldPath = pFilePath.c_str();
		// These are data types defined in the "dirent" header
		FILE * pFile;
		  pFile = fopen (pFilePath.c_str(),"wb");
		  if (pFile!=NULL)
		  {
			  if (pContent!="")
				fputs (pContent.c_str(),pFile);
			fclose (pFile);
			return true;
		  }
		return false;		
	} catch(...)
	{
		throw "Error occured while creating file.";
	}
}
	