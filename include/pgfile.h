/*
    ParaGUI - crossplatform widgetset
    Copyright (C) 2000,2001,2002  Alexander Pipelka
 
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.
 
    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.
 
    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 
    Alexander Pipelka
    pipelka@teleweb.at
 
    Last Update:      $Author: braindead $
    Update Date:      $Date: 2002/04/15 13:35:35 $
    Source File:      $Source: /sources/paragui/paragui/include/pgfile.h,v $
    CVS/RCS Revision: $Revision: 1.3 $
    Status:           $State: Exp $
*/

/** \file pgfile.h
	Header file of the PG_File class.
*/

#ifndef PG_FILE_H
#define PG_FILE_H

#ifdef SWIG
%include "swigcommon.h"
%module pgfile
%{
#include "pgfile.h"
%}
#endif

#include "paragui.h"

/**
 * @author Alexander Pipelka
 *
 * @short file abstraction for the PhsicsFS (used in conjunction with PG_FileArchive)
*/

class DECLSPEC PG_File {
protected:
	/**
	The constructor can only be called from PG_FileArchive or any subclass.
	PG_File object are create by PG_FileArchive::OpenFile(...)
	@param f pointer to PhysicsFS file
	*/
	PG_File(void* f);

public:
	~PG_File();

	// lowlevel physfs functions

	/**
	read bytes from the stream
	@param buffer	buffer to fill
	@param bytestoread number of bytes to read from the stream
	@return number of bytes read
	*/
	int read(void *buffer, unsigned int bytestoread);

	/**
	write bytes to the stream
	@param buffer	buffer to write
	@param bytestowrite number of bytes to write to the stream
	@return number of bytes written
	*/
	int write(void *buffer, unsigned int bytestowrite);

#ifndef SWIG
	//! write bytes to the stream
	/*! 
	\param buffer buffer to write
	\return number of bytes written
	*/
	int write(std::string &buffer);
#endif

#ifndef SWIG
	//! write bytes to the stream
	/*! 
	\param buffer buffer to write
	\return number of bytes written
	*/
	int write(const char *buffer);
#endif

#ifndef SWIG
	/**
	read records from the stream
	@param buffer	buffer to fill
	@param objSize size (in bytes) of a record
	@param objCount number of records to read
	@return number of records read
	*/
	int read(void *buffer, unsigned int objSize, unsigned int objCount);
#endif

#ifndef SWIG
	/**
	write records to the stream
	@param buffer	buffer to write
	@param objSize size (in bytes) of a record
	@param objCount number of records to write
	@return number of records written
	*/
	int write(void *buffer, unsigned int objSize, unsigned int objCount);
#endif

	/**
	check for the end of the file.
	@return true if we touched the end of the file.
	*/
	bool eof();
	
	/**
	get the current position in the file stream
	@return current file stream position
	*/
	int tell();
	
	/**
	set the file pointer to a given position
	@param pos position to set
	@return true on success
	*/
	bool seek(int pos);
	
	/**
	return the length of the file (in bytes)
	@return length of the file
	*/
	int fileLength();

private:
	void* file;

#ifndef SWIG
	friend class PG_FileArchive;
#endif
};

#endif
