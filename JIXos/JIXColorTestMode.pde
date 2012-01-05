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
// Color Test Mode: cycle through R, G, B
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// Public API
//----------------------------------------------------------------------------------------

unsigned int colorTestMode(uint8_t hourLeft, 
                           uint8_t hourRight, 
                           uint8_t minuteLeft, 
                           uint8_t minuteRight,
                           uint8_t secondLeft, 
                           uint8_t secondRight, 
                           uint8_t luminosity,
                           bool    hold);

//----------------------------------------------------------------------------------------
// Variables
//----------------------------------------------------------------------------------------
uint8_t colorTestModeToggle = 0;

//----------------------------------------------------------------------------------------
// Public API Implementation
//----------------------------------------------------------------------------------------

unsigned int colorTestMode(uint8_t hourLeft, 
                           uint8_t hourRight, 
                           uint8_t minuteLeft, 
                           uint8_t minuteRight, 
                           uint8_t secondLeft, 
                           uint8_t secondRight, 
                           uint8_t luminosity,
                           bool    hold)
{
  ledsBegin();
  
  for (uint8_t ledNumber = 1; ledNumber <= 27; ledNumber++)
  {
    if (colorTestModeToggle < 3)
      ledsSetRGBColor(ledNumber, 255, 0, 0);
    else if (colorTestModeToggle < 6)
      ledsSetRGBColor(ledNumber, 0, 255, 0);
    else if (colorTestModeToggle < 9)
      ledsSetRGBColor(ledNumber, 0, 0, 255);
  }
  
  ledsEnd();
  
  if (!hold)
  {
    colorTestModeToggle++;
    if (colorTestModeToggle >= 9)
      colorTestModeToggle = 0;
  }
  
  return 1000;
}

