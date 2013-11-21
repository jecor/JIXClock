//----------------------------------------------------------------------------------------
// JIXos: JIX Clock operating system
// Copyright (c) 2010-2013 Jérôme Cornet <jerome@aldorande.net>
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
// Second Mode with Tetris-like display
//----------------------------------------------------------------------------------------
#ifndef JIX_SECONDSMODE_H
#define JIX_SECONDSMODE_H

#include <Arduino.h>

//----------------------------------------------------------------------------------------
// Public API
//----------------------------------------------------------------------------------------

unsigned int secondsMode(uint8_t hourLeft, 
                         uint8_t hourRight, 
                         uint8_t minuteLeft, 
                         uint8_t minuteRight, 
                         uint8_t secondLeft, 
                         uint8_t secondRight, 
                         uint8_t luminosity,
                         bool    hold);

#endif

