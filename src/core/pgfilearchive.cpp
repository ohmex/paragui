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
    Update Date:      $Date: 2002/04/26 12:43:22 $
    Source File:      $Source: /sources/paragui/paragui/src/core/pgfilearchive.cpp,v $
    CVS/RCS Revision: $Revision: 1.2 $
    Status:           $State: Exp $
*/

#include "physfs.h"
#include "pgfilearchive.h"
#include "pgapplication.h"
#include "pglog.h"
#include "pgfont.h"

#ifdef HAVE_SDLIMAGE
#include "SDL_image.h"
#endif

Uint32 PG_FileArchive::my_instance_count = 0;
PG_SurfaceCache PG_FileArchive::my_cache;

PG_FileArchive::PG_FileArchive() {

	// increment instance count
	my_instance_count++;

	// First instance ? -> initialize PhysFS
	if(my_instance_count == 1) {
		if(PHYSFS_init("paragui") == 0) {
			PG_LogERR("Unable to initialize PhysicsFS !");
			return;
		}
	}

}

PG_FileArchive::~PG_FileArchive() {

	if(my_instance_count == 0) {
		return;
	}
	
	// decrement instance count
	my_instance_count--;

	if(my_instance_count == 0) {
		Deinit();
	}
}

void PG_FileArchive::Deinit() {
	//PHYSFS_deinit();
}

std::string *PG_FileArchive::PathToPlatform(const char *path) {
	std::string *newpath;
	const char* sep = GetDirSeparator();
	std::string::size_type pos = 0, incr;
	newpath = new std::string(path);
	incr = strlen(sep);
	if(incr == 1 && sep[0] == '/')
		return newpath;

	while( (pos = newpath->find("/", pos)) != std::string::npos) {
		newpath->replace(pos, 1, sep);
		pos += incr;
	}
	return newpath;
}


bool PG_FileArchive::AddArchive(const char* arch, bool append) {
	std::string *newpath = PathToPlatform(arch);
	bool ret = (PHYSFS_addToSearchPath(newpath->c_str(),  append) != 0);
	delete newpath;
	return ret;
}

bool PG_FileArchive::RemoveArchive(const char* arch) {
	std::string *newpath = PathToPlatform(arch);
	bool ret = (PHYSFS_removeFromSearchPath(newpath->c_str()) != 0);
	delete newpath;
	return ret;
}

char **PG_FileArchive::EnumerateFiles(const char *dir) {
	return PHYSFS_enumerateFiles(dir);
}

bool PG_FileArchive::Exists(const char *filename) {
	return PHYSFS_exists(filename);
}

bool PG_FileArchive::IsDirectory(const char *filename) {
	return PHYSFS_isDirectory(filename);
}

const char* PG_FileArchive::GetDirSeparator() {
	return PHYSFS_getDirSeparator();
}

const char* PG_FileArchive::GetRealDir(const char* filename) {
	return PHYSFS_getRealDir(filename);
}

const char* PG_FileArchive::GetLastError() {
	return PHYSFS_getLastError();
}

const char* PG_FileArchive::GetBaseDir() {
	return PHYSFS_getBaseDir();
}

const char* PG_FileArchive::GetUserDir() {
	return PHYSFS_getUserDir();
}

const char* PG_FileArchive::GetWriteDir() {
	return PHYSFS_getWriteDir();
}

PG_File* PG_FileArchive::OpenFile(const char* filename, PG_OPEN_MODE mode) {
	PHYSFS_file* file = 0;
	switch(mode) {
	case PG_OPEN_READ:
		file = PHYSFS_openRead(filename);
		break;
	case PG_OPEN_WRITE:
		file = PHYSFS_openWrite(filename);
		break;
	case PG_OPEN_APPEND:
		file = PHYSFS_openAppend(filename);
		break;
	}
	if(file == NULL) {
		return NULL;
	}

	return new PG_File(file);
}

bool PG_FileArchive::MakeDir(const char* dir) {
	return PHYSFS_mkdir(dir) == 1;
}
bool PG_FileArchive::SetWriteDir(const char* dir) {
	if(PHYSFS_setWriteDir(dir)) {
		return PHYSFS_addToSearchPath(dir, 0) == 1;
	} else {
		return false;
	}
}

bool PG_FileArchive::SetSaneConfig(const char *organization,
				   const char* appName,
				  const char* archiveExt,
				  bool includeCdRoms,
				  bool archivesFirst)
{
	if(!appName || !organization) {
		return false;
	}
	return PHYSFS_setSaneConfig(organization, appName, archiveExt,
				    includeCdRoms, archivesFirst) == 1;
}


PG_DataContainer* PG_FileArchive::ReadFile(const char* filename) {
	PG_File *file = OpenFile(filename);

	if(!file) {
		return 0;
	}

	int size = file->fileLength();

	if(size <= 0) {
		delete file;
		return 0;
	}

	PG_DataContainer* data = new PG_DataContainer(size);

	if(file->read(data->data(), size, 1) != 1) {
		delete data;
		delete file;
		return NULL;
	}

	delete file;

	return data;
}

SDL_Surface* PG_FileArchive::LoadSurface(const char* filename, bool convert) {
	if(filename == NULL) {
		return NULL;
	}

	std::string fn = filename;

	if(fn == "none") {
		return NULL;
	}

	// take a look into the cache
	SDL_Surface* surface = my_cache.FindSurface(fn);

	// return the cache surface if it has been found
	if(surface != NULL) {
		my_cache.IncRef(fn);
		return surface;
	}

	PG_DataContainer* srfdata = ReadFile(filename);
	if(!srfdata) {
		PG_LogWRN("Unable to load '%s' !", filename);
		return NULL;
	}

	surface = NULL;
	SDL_RWops *rw = SDL_RWFromMem(srfdata->data(), srfdata->size());
	
#ifdef HAVE_SDLIMAGE
	surface = IMG_Load_RW(rw, 1);
#else
	surface = SDL_LoadBMP_RW(rw, 1);
#endif
	
	delete srfdata;
	
	if(convert && !PG_Application::GetGLMode()) {
		SDL_Surface* tmpsrf = SDL_DisplayFormat(surface);
		if(tmpsrf) {
			SDL_FreeSurface(surface);
			surface = tmpsrf;
		}
	}

	// add the loaded surface to the cache
	my_cache.AddSurface(fn, surface);

	// return the pointer to the surface
	return surface;
}

bool PG_FileArchive::UnloadSurface(SDL_Surface* surface, bool bDeleteIfNotExists) {
	my_cache.DeleteSurface(surface, bDeleteIfNotExists);
	return true;
}

bool PG_FileArchive::RemoveAllArchives() {
	char** i = GetSearchPath();
	char** d;
	bool success = true;

	for(d = i; *d != NULL; d++) {
		if(!RemoveArchive(*d)) {
			PG_LogWRN("Unable to remove '%s' from searchpath!", *d);
			success = false;
		}
	}

	FreeList(i);
	return success;
}

char** PG_FileArchive::GetSearchPath() {
	return PHYSFS_getSearchPath();
}

void PG_FileArchive::FreeList(void* list) {
	PHYSFS_freeList(list);
}

void PG_FileArchive::EnableSymlinks(bool followSymlinks) {
	PHYSFS_permitSymbolicLinks(followSymlinks);
}

/*
 * Local Variables:
 * c-basic-offset: 8
 * End:
 */