/*
 * JIXClock SDK
 * Copyright (c) 2012-2013 Jérôme Cornet
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "SDL.h"

//-----------------------------------------------------------------
// Constants and global variables
//-----------------------------------------------------------------
#define CLOCK_ASPECT_RATIO 3.44
#define SQUARE_SIZE_RATIO  17.2
#define BORDER_SIZE_RATIO  25.8
#define INTER_SIZE_RATIO   10.32
#define MINI_SIZE_RATIO    51.6

//-----------------------------------------------------------------
// Functions
//-----------------------------------------------------------------
void drawLEDs(SDL_Surface * screen);

void drawBackground(SDL_Surface *screen);

SDL_Surface * createScreen(Uint16 w, Uint16 h, Uint8 bpp, Uint32 flags);
