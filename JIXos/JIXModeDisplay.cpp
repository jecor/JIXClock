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
// Display of current mode (used when changing mode)
//----------------------------------------------------------------------------------------
#include "JIXLEDS.h"
#include "JIXModeDisplay.h"

//----------------------------------------------------------------------------------------
// Constants
//----------------------------------------------------------------------------------------
const unsigned int globalNbModes = 14;
extern unsigned int globalLuminosity;

const uint8_t modeDisplayScanOrder[27] = { 25, 16, 17, 18, 10, 11, 1, 2, 3,
                                           26, 19, 20, 21, 12, 13, 4, 5, 6,
                                           27, 22, 23, 24, 14, 15, 7, 8, 9 };


//----------------------------------------------------------------------------------------
// Public API Implementation
//----------------------------------------------------------------------------------------

void modeDisplay(uint8_t mode)
{
  uint8_t h = 0;
  uint8_t hIncrement = 255/globalNbModes;
  
  ledsBegin();
  
  for (uint8_t number = 0; number < 27; number++)
  {
    if (number <= mode)
    {
      ledsSetColor(modeDisplayScanOrder[number], h, 255, globalLuminosity);
      h += hIncrement;
    }
    else
    {
      ledsSetColor(modeDisplayScanOrder[number], h, 255, 0);
    }
  }
  
  ledsEnd();
}

