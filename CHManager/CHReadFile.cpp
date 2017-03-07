/*************************************************************************************
*			© Copyright MSL Software, S.L., 2002
*	This document is the property of MSL Software and its content is confidential. 
*   This work must not be reproduced or	disclosed to others or used for purposes 
*   other than that for which it is supplied without MSL's prior written permission.
*	MSL must not be considered liable for any mistake or omission in the edition of 
*   this document. "MSL" is a registered trademark.	
*
*	File name	:CHReadFile.h
*	Description	:
*
*	Author		:Chess Team
*	Date created:21/12/2005
* 	Project		:Chess Management
*	
* 	Modification history
*	By		:
*	Date	:
*	Changes	:
*
***************************************************************************************/

#include "stdAfx.h"
#include <io.h>
#include <fcntl.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <share.h>
#include "CHReadFile.h"

//////////////////////////////////////////////////////////////////////
// Member functions
//////////////////////////////////////////////////////////////////////

void CHReadFile::saveFile(RWCString file)
{
	int fh=_sopen(fileName,_O_WRONLY|_O_CREAT,_SH_DENYNO,_S_IWRITE);
	if (fh == -1) 
	{
		validFile = false ;
		return;
	}
	
	_write(fh,file,file.length());


	_close(fh);
}

void CHReadFile::readFile()
{
	int fh=_sopen(fileName,_O_BINARY|_O_RDONLY,_SH_DENYWR,_S_IREAD);
	if (fh == -1) 
	{
		validFile = false ;
		return;
	}

	long fileLength=_filelength(fh);
	if( fileLength==-1L )
	{
		_close(fh);
		return;
	}

	if( generateBuffer(fileLength) )
	{
		_read(fh,buffer,fileLength);
	}


	_close(fh);
}

RWBoolean CHReadFile::getLine(RWCString& target)
{
	char *p=strstr(buffer+offset,"\x0a");
	if( p )
	{
		unsigned long dzh=offset;
		offset=(p-buffer)+1;
		target=RWCString(buffer+dzh,offset-dzh);
	}
	return p!=0;
}

RWBoolean CHReadFile::generateBuffer(long size)
{
	if( buffer )
	{
		delete [] buffer;
		buffer=0;
	}

	buffer=new char[size];
	return buffer!=0;
}
