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

#if !defined(AFX_READFILE_H__22BECBE5_5083_11D3_853E_0060949720DD__INCLUDED_)
#define AFX_READFILE_H__22BECBE5_5083_11D3_853E_0060949720DD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __RWCSTRING_H__
#	include <rw/cstring.h>
#endif // __RWCSTRING_H__

class CHReadFile  
{
public:
	inline CHReadFile()
		:buffer(0)
		,fileName("")
		,offset(0L)
		,validFile(true)
		{}
	inline CHReadFile(RWCString name)
		:buffer(0)
		,fileName(name)
		,offset(0L)
		,validFile(true)
		{	readFile(); }
	inline virtual ~CHReadFile()
	{	if( buffer )
			delete [] buffer;
	}
	inline void setFileName(RWCString name)
		{ fileName = name;}

	inline char * getBuffer() const
		{ return buffer; }
	inline CString getFileName() const
		{ return fileName; }
	inline RWBoolean getValidFile() const
		{ return validFile; }

	RWBoolean getLine(RWCString& target);

	virtual void saveFile(RWCString file);

private:
	virtual void readFile();
	

	RWBoolean generateBuffer(long size);

private:
	char *buffer;
	RWCString fileName;
	unsigned long offset;
	RWBoolean validFile;
};

#endif // !defined(AFX_READFILE_H__22BECBE5_5083_11D3_853E_0060949720DD__INCLUDED_)
