/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * file-op.h
 */

#ifndef _FILE_OP_H_
#define _FILE_OP_H_

#include <stdio.h>
#include <dirent.h>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>

class FileOP
{
public:
	
	static bool createNewFile(const std::string&,const std::string&);
	
	static bool fileExists (const std::string&);
	static bool removeFile(const std::string&);
protected:

private:

};

#endif // _FILE_OP_H_

