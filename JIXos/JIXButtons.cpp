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
// Buttons management
//----------------------------------------------------------------------------------------
#include "JIXButtons.h"

//----------------------------------------------------------------------------------------
// Constants
//----------------------------------------------------------------------------------------

const unsigned int SETH_PIN = 4;
const unsigned int SETM_PIN = 12;

//----------------------------------------------------------------------------------------
// Implementation
//----------------------------------------------------------------------------------------

void buttonsInit()
{
  pinMode(SETH_PIN, INPUT);
  pinMode(SETM_PIN, INPUT);
}

bool buttonsGetModeState()
{
   return (digitalRead(SETH_PIN) == 0);
}

bool buttonsGetIncrementState()
{
  return (digitalRead(SETM_PIN) == 0);
}


