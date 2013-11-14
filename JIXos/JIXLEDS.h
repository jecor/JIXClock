//----------------------------------------------------------------------------------------
// JIXos: JIX Clock operating system
// Copyright (c) 2010-2011 Jérôme Cornet <jerome@aldorande.net>
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//----------------------------------------------------------------------------------------
// RGB LEDs Management
//----------------------------------------------------------------------------------------
#ifndef JIX_LEDS_H
#define JIX_LEDS_H

#include <Arduino.h>

//----------------------------------------------------------------------------------------
// Public API
//----------------------------------------------------------------------------------------

// Initialize LEDS
void ledsInit();  

// Call before updating the LEDs
void ledsBegin();

// Call after updating the LEDs
void ledsEnd();

// Set the HSL color of the LED #ledNumber. ledNumber is in [1..27]
void ledsSetColor(uint8_t ledNumber, uint8_t h, uint8_t s, uint8_t l);

// Set the RGB color of the LED #ledNumber
void ledsSetRGBColor(uint8_t ledNumber, uint8_t r, uint8_t g, uint8_t b);

#endif

