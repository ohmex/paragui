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
    Update Date:      $Date: 2002/04/15 13:22:30 $
    Source File:      $Source: /sources/paragui/paragui/include/pglineedit.h,v $
    CVS/RCS Revision: $Revision: 1.1 $
    Status:           $State: Exp $
*/

#ifndef PG_LINEEDIT
#define PG_LINEEDIT

#ifdef SWIG
%include "swigcommon.h"
%module pglineedit
%{
#include "pglineedit.h"
%}
#endif

#include "pgthemewidget.h"
#include <string>

/**
	@author Alexander Pipelka
 
	@short An editable text box.
 
	This really should be renamed to PG_TextBox or something similar, because
	PG_LineEdit really makes no sense :).  Also the 'Edit' part implies that
	it will always be modifiable, but having a modifyable attribute would
	probably be better than creating a whole new widget for an unmodifiable
	text box.
*/
class DECLSPEC PG_LineEdit : public PG_ThemeWidget {
public:

	/** */
	PG_LineEdit(PG_Widget* parent, const PG_Rect& r, const char* style="LineEdit", int maximumLength = 1000000);

	/** */
	~PG_LineEdit();

	void LoadThemeStyle(const char* widgettype);

#ifndef SWIG
	/** */
	void LoadThemeStyle(const char* widgettype, const char* objectname);
#endif

	/** start edit */
	void EditBegin();

	/** */
	void EditEnd();

	/** */
	void SetCursorPos(int p);

	/** */
	int GetCursorPos();

	/**
	Set the current text string
	@param	new_text	pointer to text string
	*/
	virtual void SetText(const char* new_text);

	/** */
	bool IsCursorVisible();

	/**
	Send a char into the LineEdit widget

	@param	c		the character to insert
	*/
	void SendChar(char c);

	/**
	Send a 'del' keystroke into the LineEdit widget
	*/
	void SendDel();

	/**
	Send a 'BKSPC' keystroke into the LineEdit widget
	*/
	void SendBackspace();

	/**
	Define a set of valid keys

	@param	keys		a string which contains all valid chars
	*/
	void SetValidKeys(const char* keys);

	/**
	Set if the widget is editable by the user
	@param	edit		true - widget is editable / false - widget is read only
	*/
	void SetEditable(bool edit);

	/**
	Check if the widget is editable by the user
	@return			true - widget is editable / false - widget is read only
	*/
	bool GetEditable();

	/**
	Set password character (witch will be displayed in place of letter)
	@param	passchar		character (if = 0 do not any replacement)
	*/
	void SetPassHidden(char passchar);

	/**
	Return setted passchar
	@return			Returns character, witch is displayed in place on letters
	*/
	char GetPassHidden(void);

	bool Action(PG_ACTION action);


protected:

	/** */
	virtual void InsertChar(const char* c);

	/** */
	virtual void DeleteChar(Uint16 pos);

	/** */
	void CopyText(bool del = false);

	/** */
	void PasteText(Uint16 pos);

	/** */
	void StartMark(Uint16 pos);

	/** */
	void EndMark(Uint16 pos);

	/** */
	virtual bool eventFilterKey(const SDL_KeyboardEvent* key);

	/** */
	virtual void eventEditBegin(int id, PG_Widget* widget, unsigned long data, void *clientdata);

	/** */
	virtual void eventEditEnd(int id, PG_Widget* widget, unsigned long data, void *clientdata);

	/** */
	void eventBlit(SDL_Surface* surface, const PG_Rect& src, const PG_Rect& dst);
	//void eventDraw(SDL_Surface* surface, const PG_Rect& rect);

	/** */
	bool eventKeyDown(const SDL_KeyboardEvent* key);

	/** */
	bool eventMouseButtonDown(const SDL_MouseButtonEvent* button);

	/** */
	void eventInputFocusLost(PG_MessageObject* newfocus);

	void eventHide();

	int my_cursorPosition;

private:
#ifndef SWIG

	PG_LineEdit(const PG_LineEdit&);
	PG_LineEdit& operator=(PG_LineEdit&);
#endif

	void DrawText(const PG_Rect& dst);
	void DrawTextCursor();
	Uint16 GetCursorXPos();
	const char* GetDrawText();
	int GetCursorPosFromScreen(int x, int y);

	bool IsValidKey(char c);

	std::string my_buffer;
	int my_startMark;
	int my_endMark;

	bool my_isCursorVisible;
	int my_offsetX;
	std::string my_validkeys;
	bool my_isEditable;
	int my_maximumLength;

	char my_passchar;

	SDL_Surface* my_srfTextCursor;
};

#endif // PG_LINEEDIT
