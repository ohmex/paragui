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
    Update Date:      $Date: 2002/04/15 14:53:56 $
    Source File:      $Source: /sources/paragui/paragui/src/core/pgfile.cpp,v $
    CVS/RCS Revision: $Revision: 1.1 $
    Status:           $State: Exp $
*/

#include "pgfile.h"
#include "physfs.h"

PG_File::PG_File(void* f) :
file(f) {}

PG_File::~PG_File() {
	if(file != NULL) {
		PHYSFS_close((PHYSFS_file*)file);
	}
}

int PG_File::read(void *buffer, unsigned int bytestoread) {
	return read(buffer, 1, bytestoread);
}

int PG_File::write(void *buffer, unsigned int bytestowrite) {
	return write(buffer, 1, bytestowrite);
}

int PG_File::write(std::string &buffer) {
  	return write(const_cast<char*>(buffer.c_str()), 1, buffer.length());
}

int PG_File::write(const char *buffer) {
	return write(const_cast<char*>(buffer), 1, strlen(buffer));
}

int PG_File::read(void *buffer, unsigned int objSize, unsigned int objCount) {
	return PHYSFS_read((PHYSFS_file*)file, buffer, objSize, objCount);
}

int PG_File::write(void *buffer, unsigned int objSize, unsigned int objCount) {
	return PHYSFS_write((PHYSFS_file*)file, buffer, objSize, objCount);
}

bool PG_File::eof() {
	return PHYSFS_eof((PHYSFS_file*)file);
}

int PG_File::tell() {
	return PHYSFS_tell((PHYSFS_file*)file);
}

bool PG_File::seek(int pos) {
	return PHYSFS_seek((PHYSFS_file*)file, pos);
}

int PG_File::fileLength() {
	return PHYSFS_fileLength((PHYSFS_file*)file);
}