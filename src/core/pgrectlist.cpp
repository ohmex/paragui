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
    Source File:      $Source: /sources/paragui/paragui/src/core/pgrectlist.cpp,v $
    CVS/RCS Revision: $Revision: 1.1 $
    Status:           $State: Exp $
*/

#include "pgrectlist.h"
#include "pgwidget.h"
#include "pgapplication.h"
#include "pglog.h"

#include <algorithm>

PG_RectList::PG_RectList() {}

PG_RectList::~PG_RectList() {}

PG_RectList PG_RectList::Intersect(PG_Rect* rect, int first, int last) {
	PG_RectList result;
	int s = (last == -1) ? size() : last;

	PG_Widget* testwidget;
	PG_Rect* testrect;

	// clear previous list
	result.clear();

	// loop through all rects
	for(int i=first; i<s; i++) {

		// get the next rectangle to test
		testwidget = (*this)[i];

		if(!testwidget->IsVisible()) {
			continue;
		}

		testrect = testwidget->GetClipRect();
		if(rect->OverlapRect(*testrect)) {
			// append the matching rectangle
			result.Add(testwidget);
		}
	}

	return result;
}

PG_Widget* PG_RectList::IsInside(const PG_Point& p) {
	PG_Widget* result = NULL;
	PG_Widget* testrect;

	// loop down all rects till we find a match
	for(int i=size()-1; i>=0; i--) {

		testrect = (*this)[i];

		// check if the tested rect is visible
		if(!testrect->IsVisible()) {
			continue;
		}

		// check for a match
		if(testrect->GetClipRect()->IsInside(p)) {
			result = testrect;
			break;
		}
	}

	return result;
}

void PG_RectList::Add(PG_Widget* rect) {
	indexmap[rect] = size();
	
	/*iterator i = find(begin(), end(), rect);
		
	if(i != end()) {
		PG_LogWRN("Trying to add an existing entry to the rectlist!");
		return;
	}*/
	
	push_back(rect);
}

void PG_RectList::UpdateIndexMap() {
	indexmap.clear();

	int index = 0;
	for(iterator i = begin(); i != end(); i++) {
		indexmap[(*i)] = index;
		index++;
	}
}

bool PG_RectList::Remove(PG_Rect* rect) {
	iterator mark = end();

	int index = 0;
	for(iterator i = begin(); i != end(); i++) {
		indexmap.erase((*i));
		if(*i == rect) {
			mark = i;
		} else {
			indexmap[(*i)] = index;
			index++;
		}
	}

	if(mark != end()) {
		erase(mark);
		return true;
	}

	return false;
}

int PG_RectList::FindIndexOf(PG_Rect* rect) {
	int index = -1;

	PG_RectListMap::iterator im = indexmap.find(rect);

	if(im != indexmap.end()) {
		index = (*im).second;
	}

	return index;
}

void PG_RectList::Blit(const PG_Rect& rect) {
	PG_RectList* childs;
	static SDL_Surface* screen = PG_Application::GetScreen();

	// store old clipping rectangle
	PG_Rect o;
	SDL_GetClipRect(screen, &o);

	// blit all objects in the list
	for(iterator i = begin(); i != end(); i++) {

		if(!(*i)->IsVisible()) {
			continue;
		}

		// calculate the clipping rectangle
		// cliprect = blittingregion / widgetcliprect
		PG_Rect* cr = (*i)->GetClipRect();
		PG_Rect c = cr->IntersectRect(rect);
		SDL_SetClipRect(screen, &c);

		// blit it
		(*i)->Blit(false, false);

		// blit all children of the widget
		childs = (*i)->GetChildList();
		if(childs) {
			childs->Intersect((PG_Rect*)&rect).Blit();
		}
	}

	// reset clipping rectangle
	SDL_SetClipRect(PG_Application::GetScreen(), &o);
}

void PG_RectList::Blit() {
	// blit all objects in the list
	for(iterator i = begin(); i != end(); i++) {
		if(!(*i)->IsVisible()) {
			continue;
		}

		(*i)->Blit(true, false);
	}
}

bool PG_RectList::BringToFront(PG_Widget* rect) {
	PG_RectListMap::iterator i = indexmap.find(rect);

	if(i == indexmap.end()) {
		return false;
	}

	Remove(rect);
	Add(rect);

	return true;
}

bool PG_RectList::SendToBack(PG_Widget* rect) {
	if(!Remove(rect)) {
		return false;
	}

	insert(begin(), rect);
	UpdateIndexMap();

	return true;
}