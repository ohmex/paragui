/*
    ParaGUI - crossplatform widgetset
    setpixel - draw a single pixel onto a surface

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
    Update Date:      $Date: 2002/04/15 13:22:10 $
    Source File:      $Source: /sources/paragui/paragui/src/draw/setpixel.cpp,v $
    CVS/RCS Revision: $Revision: 1.1 $
    Status:           $State: Exp $
*/

#include "pgdraw.h"

void PG_Draw::SetPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b, SDL_Surface * surface) {
	static Uint8 old_r = 0;
	static Uint8 old_g = 0;
	static Uint8 old_b = 0;
	static Uint8 ri, gi, bi;

	static Uint32 pixel;
	static Uint8 *bits;
	static Uint8 bpp;

	static SDL_Rect rect;
	SDL_GetClipRect(surface, &rect);

	if((x < rect.x) || (y < rect.y)) {
		return;
	}

	if((x >= rect.x+rect.w) || (y >= rect.y+rect.h)) {
		return;
	}

	bpp = surface->format->BytesPerPixel;
	bits = ((Uint8 *) surface->pixels) + y * surface->pitch + x * bpp;

	if(!((old_r==r) && (old_g==g) && (old_b==b))) {
		pixel = SDL_MapRGB(surface->format, r, g, b);
		old_r = r;
		old_g = g;
		old_b = b;
	}

	/* Set the pixel */
	switch (bpp) {
		case 1:
			*((Uint8 *) (bits)) = (Uint8) pixel;
			break;

		case 2:
			*((Uint16 *) (bits)) = (Uint16) pixel;
			break;

		case 3: {			/* Format/endian independent */
				ri = (pixel >> surface->format->Rshift) & 0xFF;
				gi = (pixel >> surface->format->Gshift) & 0xFF;
				bi = (pixel >> surface->format->Bshift) & 0xFF;
				*((bits) + surface->format->Rshift / 8) = ri;
				*((bits) + surface->format->Gshift / 8) = gi;
				*((bits) + surface->format->Bshift / 8) = bi;
			}
			break;

		case 4:
			*((Uint32 *) (bits)) = (Uint32) pixel;
			break;
	}
}
