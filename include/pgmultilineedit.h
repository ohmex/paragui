#ifndef PG_MULTI_LINE_EDIT 
#define PG_MULTI_LINE_EDIT 

#include "pglineedit.h"
#include "pgscrollbar.h"
#include "pgtheme.h"
#include "pgstring.h"

class DECLSPEC PG_MultiLineEdit : public PG_LineEdit {
public:

	PG_MultiLineEdit(PG_Widget* parent, const PG_Rect& r, const std::string& style="LineEdit", int maximumLength = 1000000);
	virtual void SetText(const std::string& new_text);	

    void SetCursorPos(int p);

    void SetVPosition(int line);

protected:

	void eventBlit(SDL_Surface* surface, const PG_Rect& src, const PG_Rect& dst);

	bool eventKeyDown(const SDL_KeyboardEvent* key);

	bool eventMouseButtonDown(const SDL_MouseButtonEvent* button);

	bool eventMouseMotion(const SDL_MouseMotionEvent* motion);

	bool eventMouseButtonUp(const SDL_MouseButtonEvent* button);

	virtual void InsertChar(const PG_Char& c);

	virtual void DeleteChar(Uint16 pos);

	bool handleScroll(PG_ScrollBar* widget, long data);

private:

    void FindWordRight();

    void FindWordLeft();

    void DeleteSelection();

    void GetCursorTextPosFromScreen(int x, int y, unsigned int& horzOffset, unsigned int& lineOffset);

    void GetCursorTextPos(unsigned int& horzOffset, unsigned int& lineOffset);

    void SetCursorTextPos(unsigned int offset, unsigned int line);

    int ConvertCursorPos(unsigned int offset, unsigned int line);

    void GetCursorPos(int& x, int& y);

    void DrawText(const PG_Rect& dst);

    void DrawTextCursor();

    void CreateTextVector(bool bSetupVScroll = true);

    void SetupVScroll();

	std::vector<PG_String> my_textdata;

    PG_ScrollBar* my_vscroll;

    int my_firstLine;

    int my_mark;

    bool my_isCursorAtEOL;

    bool my_allowHiddenCursor;	
};

#endif // PG_MULTI_LINE_EDIT
