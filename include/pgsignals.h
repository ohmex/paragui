#ifndef PG_SIGNALS_H
#define PG_SIGNALS_H

#include "SDL.h"
#include <sigc++/signal_system.h>
#include <iostream>
#include <map>

class PG_Widget;
class PG_Button;
class PG_CheckButton;
class PG_RadioButton;
class PG_ScrollBar;
class PG_Slider;
class PG_ListBoxItem;
class PG_LineEdit;
class PG_SpinnerBox;
class PG_MenuItem;
class PG_Window;
class PG_Application;
class PG_MessageObject;

using namespace SigC;

typedef void PG_Pointer;

typedef Signal1<bool, PG_Widget*> PG_SignalGeneric;

class PG_Signal0 : 
public Signal1<bool, PG_Pointer*>,
public Signal0<bool>
{
public:

	bool operator()(PG_Pointer* data) {
		Signal1<bool, PG_Pointer*>::emit(data);
		Signal0<bool>::emit();
	};
	
	bool operator()() {
		Signal1<bool, PG_Pointer*>::emit(data);
		Signal0<bool>::emit();
	};

	Connection connect(const Slot1<bool, PG_Pointer*>& s, PG_Pointer* _data = NULL) {
		data = _data;
		return Signal1<bool, PG_Pointer*>::connect(s);
	};

	Connection connect(const Slot0<bool>& s) {
		return Signal0<bool>::connect(s);
	};

private:
	PG_Pointer* data;
};

template<class P1>
class PG_Signal1 : 
public Signal2<bool, P1, PG_Pointer*>,
public Signal1<bool, PG_Pointer*>,
public Signal1<bool, P1>,
public Signal0<bool>
{
public:

	virtual ~PG_Signal1() {};
	
	virtual bool operator()(P1 p1, PG_Pointer* data) {
		return
			Signal2<bool, P1, PG_Pointer*>::emit(p1, data) |
			Signal1<bool, PG_Pointer*>::emit(data) |
			Signal1<bool, P1>::emit(p1) |
			Signal0<bool>::emit();
	}
	
	virtual bool operator()(P1 p1) {
		return
			Signal2<bool, P1, PG_Pointer*>::emit(p1, data) |
			Signal1<bool, PG_Pointer*>::emit(data) |
			Signal1<bool, P1>::emit(p1) |
			Signal0<bool>::emit();
	};

	virtual bool operator()(PG_Pointer* data) {
		return
			Signal1<bool, PG_Pointer*>::emit(data) |
			Signal0<bool>::emit();
	};

	virtual bool operator()() {
		return
			Signal0<bool>::emit();
	};
	
	virtual Connection connect(const Slot2<bool, P1, PG_Pointer*>& s, PG_Pointer* _data = NULL) {
		data = _data;
		return Signal2<bool, P1, PG_Pointer*>::connect(s);
	};

	virtual Connection connect(const Slot1<bool, PG_Pointer*>& s, PG_Pointer* _data = NULL) {
		data = _data;
		return Signal1<bool, PG_Pointer*>::connect(s);
	};

	virtual Connection connect(const Slot1<bool, P1>& s) {
		return Signal1<bool, P1>::connect(s);
	}

	virtual Connection connect(const Slot0<bool>& s, PG_Pointer* _data) {
		data = _data;
		return Signal0<bool>::connect(s);
	};

	virtual Connection connect(const Slot0<bool>& s) {
		return Signal0<bool>::connect(s);
	};


private:
	PG_Pointer* data;
};


template<class P1, class P2>
class PG_Signal2 : 
public Signal3<bool, P1, P2, PG_Pointer*>,
public Signal2<bool, P1, P2>,
public Signal1<bool, P2>,

public Signal2<bool, P1, PG_Pointer*>,
public Signal1<bool, PG_Pointer*>,
public Signal1<bool, P1>,
public Signal0<bool>
{
public:

	virtual ~PG_Signal2() {};
	
	virtual bool operator()(P1 p1, P2 p2, PG_Pointer* data) {
		return
			Signal3<bool, P1, P2, PG_Pointer*>::emit(p1, p2, data) |
			Signal2<bool, P1, P2>::emit(p1, p2) |
			Signal1<bool, P2>::emit(p2) |

			Signal2<bool, P1, PG_Pointer*>::emit(p1, data) |
			Signal1<bool, PG_Pointer*>::emit(data) |
			Signal1<bool, P1>::emit(p1) |
			Signal0<bool>::emit();
	}

	virtual bool operator()(P1 p1, P2 p2) {
		return
			Signal3<bool, P1, P2, PG_Pointer*>::emit(p1, p2, data) |
			Signal2<bool, P1, P2>::emit(p1, p2) |
			Signal1<bool, P2>::emit(p2) |

			Signal2<bool, P1, PG_Pointer*>::emit(p1, data) |
			Signal1<bool, PG_Pointer*>::emit(data) |
			Signal1<bool, P1>::emit(p1) |
			Signal0<bool>::emit();
	}
	
	virtual bool operator()(P1 p1, PG_Pointer* data) {
		return
			Signal2<bool, P1, PG_Pointer*>::emit(p1, data) |
			Signal1<bool, PG_Pointer*>::emit(data) |
			Signal1<bool, P1>::emit(p1) |
			Signal0<bool>::emit();
	}

	virtual bool operator()(P1 p1) {
		return
			Signal2<bool, P1, PG_Pointer*>::emit(p1, data) |
			Signal1<bool, PG_Pointer*>::emit(data) |
			Signal1<bool, P1>::emit(p1) |
			Signal0<bool>::emit();
	}
	
	virtual bool operator()(PG_Pointer* data ) {
		return
			Signal1<bool, PG_Pointer*>::emit(data) |
			Signal0<bool>::emit();
	}
	
	virtual bool operator()() {
		return
			Signal0<bool>::emit();
	};

	
	virtual Connection connect(const Slot3<bool, P1, P2, PG_Pointer*>& s, PG_Pointer* _data) {
		data = _data;
		return Signal3<bool, P1, P2, PG_Pointer*>::connect(s);
	}

	virtual Connection connect(const Slot2<bool, P1, P2>& s) {
		return Signal2<bool, P1, P2>::connect(s);
	}

	/*virtual Connection connect(const Slot2<bool, P2, PG_Pointer*>& s, PG_Pointer* _data) {
		data = _data;
		return Signal2<bool, P2, PG_Pointer*>::connect(s);
	}*/

	virtual Connection connect(const Slot1<bool, P2>& s) {
		return Signal1<bool, P2>::connect(s);
	}

	virtual Connection connect(const Slot2<bool, P1, PG_Pointer*>& s, PG_Pointer* _data) {
		data = _data;
		return Signal2<bool, P1, PG_Pointer*>::connect(s);
	};

	virtual Connection connect(const Slot1<bool, PG_Pointer*>& s, PG_Pointer* _data) {
		data = _data;
		return Signal1<bool, PG_Pointer*>::connect(s);
	};

	virtual Connection connect(const Slot1<bool, P1>& s) {
		return Signal1<bool, P1>::connect(s);
	}

	virtual Connection connect(const Slot0<bool>& s, PG_Pointer* _data) {
		data = _data;
		return Signal0<bool>::connect(s);
	};

	virtual Connection connect(const Slot0<bool>& s) {
		return Signal0<bool>::connect(s);
	};


private:
	PG_Pointer* data;
};


typedef PG_Signal1<PG_Button*> PG_SignalButtonClick;

typedef PG_Signal1<PG_RadioButton*> PG_SignalRadioButtonClick;

typedef PG_Signal1<PG_ListBoxItem*> PG_SignalSelectItem;

typedef PG_Signal2<PG_ScrollBar*, long> PG_SignalScrollPos;

typedef PG_Signal2<PG_ScrollBar*, long> PG_SignalScrollTrack;

typedef PG_Signal2<PG_Slider*, long> PG_SignalSlide;

typedef PG_Signal2<PG_Slider*, long> PG_SignalSlideEnd;

typedef PG_Signal2<PG_SpinnerBox*, long> PG_SignalSpinnerChange;

typedef PG_Signal1<PG_LineEdit*> PG_SignalEditBegin;

typedef PG_Signal1<PG_LineEdit*> PG_SignalEditEnd;

typedef PG_Signal1<PG_LineEdit*> PG_SignalEditReturn;

typedef Signal2<bool, PG_MenuItem*, PG_Pointer*> PG_SignalMenuItemSelected;

typedef PG_Signal1<PG_Window*> PG_SignalWindowClose;

typedef PG_Signal1<PG_Window*> PG_SignalWindowMinimize;

typedef PG_Signal1<PG_Window*> PG_SignalWindowRestore;

typedef PG_Signal1<PG_MessageObject*> PG_SignalAppIdle;

typedef PG_Signal1<PG_Application*> PG_SignalAppQuit;

typedef PG_Signal1 <const SDL_ResizeEvent*> PG_SignalVideoResize;

#endif // PG_SIGNALS_H