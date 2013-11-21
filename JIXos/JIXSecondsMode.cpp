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
// Second Mode with Tetris-like display
//----------------------------------------------------------------------------------------
#include "JIXLEDS.h"
#include "JIXSecondsMode.h"
#include "JIXStandardConstants.h"
                           
//----------------------------------------------------------------------------------------
// Private functions
//----------------------------------------------------------------------------------------

void secondsGenericDisplay(uint8_t ledStartNumber, uint8_t value, uint8_t pieceNumber, const uint8_t ** pieces, uint8_t piecesSize, uint8_t luminosity, uint8_t color);

void secondsGenericDisplay2(uint8_t ledStartNumber, uint8_t value, uint8_t value2, const uint8_t * pieces, uint8_t piecesSize, uint8_t luminosity, uint8_t color, uint8_t color2);

//----------------------------------------------------------------------------------------
// Constants
//----------------------------------------------------------------------------------------
const prog_uint8_t secondsSix[6 * 6] PROGMEM = 
            { 0, 0,
              0, 0,
              0, 0,
            
              1, 0,
              0, 0,
              0, 0,
            
              1, 1,
              0, 0,
              0, 0,
            
              1, 1,
              1, 0,
              0, 0, 
            
              1, 1,
              1, 1,
              0, 0, 
            
              1, 1,
              1, 1,
              1, 0  
            };
            
const prog_uint8_t secondsNines[10 * 9] PROGMEM = 
            { 0, 0, 0,
              0, 0, 0,
              0, 0, 0,
              
              1, 0, 0,
              0, 0, 0,
              0, 0, 0,
              
              1, 1, 0,
              0, 0, 0,
              0, 0, 0,
              
              1, 1, 1,
              0, 0, 0,
              0, 0, 0,
              
              1, 1, 1,
              1, 0, 0,
              0, 0, 0,
              
              1, 1, 1,
              1, 1, 0,
              0, 0, 0,
              
              1, 1, 1,
              1, 1, 1,
              0, 0, 0,
              
              1, 1, 1,
              1, 1, 1,
              1, 0, 0,
              
              1, 1, 1,
              1, 1, 1,
              1, 1, 0,
             
              1, 1, 1,
              1, 1, 1,
              1, 1, 1 
            };

//----------------------------------------------------------------------------------------
// Variables (to store current state of pieces for hold mode)
//----------------------------------------------------------------------------------------
uint8_t secondsPieceNumberHourLeft;
uint8_t secondsPieceNumberHourRight;
uint8_t secondsPieceNumberMinuteLeft;
uint8_t secondsPieceNumberMinuteRight;

uint8_t secondsColorHourLeft;
uint8_t secondsColorHourRight;
uint8_t secondsColorMinuteLeft;
uint8_t secondsColorMinuteRight;

bool secondsToggle = false;

//----------------------------------------------------------------------------------------
// Public API Implementation
//----------------------------------------------------------------------------------------

unsigned int secondsMode(uint8_t hourLeft, 
                         uint8_t hourRight, 
                         uint8_t minuteLeft, 
                         uint8_t minuteRight, 
                         uint8_t secondLeft, 
                         uint8_t secondRight, 
                         uint8_t luminosity,
                         bool    hold)
{  
  uint8_t pieceNumberHourLeft;
  uint8_t pieceNumberHourRight;
  uint8_t pieceNumberMinuteLeft;
  uint8_t pieceNumberMinuteRight;
  
  if (!hold && !secondsToggle)
  {
    secondsPieceNumberHourLeft    = random(standardThreesNbPieces[hourLeft]);
    secondsPieceNumberHourRight   = random(standardNinesNbPieces[hourRight]);
    secondsPieceNumberMinuteLeft  = random(standardSixNbPieces[minuteLeft]);
    secondsPieceNumberMinuteRight = random(standardNinesNbPieces[minuteRight]);
    
    secondsColorHourLeft = random(32);
    do { secondsColorHourRight   = random(32); } while (abs(secondsColorHourLeft - secondsColorHourRight) < standardColorDifference);
    
    if ((secondLeft == 0) && (secondRight == 0))
    {
      do { secondsColorMinuteLeft  = random(32); } while ((abs(secondsColorHourLeft - secondsColorMinuteLeft) < standardColorDifference) ||
                                                           (abs(secondsColorHourRight - secondsColorMinuteLeft) < standardColorDifference));
      do { secondsColorMinuteRight = random(32); } while ((abs(secondsColorHourLeft - secondsColorMinuteRight) < standardColorDifference)  ||
                                                   (abs(secondsColorHourRight - secondsColorMinuteRight) < standardColorDifference) ||
                                                   (abs(secondsColorMinuteLeft - secondsColorMinuteRight) < standardColorDifference));  
    }
                                                 
    pieceNumberHourLeft    = secondsPieceNumberHourLeft;
    pieceNumberHourRight   = secondsPieceNumberHourRight;
    pieceNumberMinuteLeft  = secondsPieceNumberMinuteLeft;
    pieceNumberMinuteRight = secondsPieceNumberMinuteRight;
  }
  else
  {
    pieceNumberHourLeft    = secondsPieceNumberHourLeft;
    pieceNumberHourRight   = secondsPieceNumberHourRight;
    pieceNumberMinuteLeft  = secondsPieceNumberMinuteLeft;
    pieceNumberMinuteRight = secondsPieceNumberMinuteRight;
    
    if ((hourLeft == 0) || (secondsPieceNumberHourLeft >= standardThreesNbPieces[hourLeft]))
    {
      pieceNumberHourLeft = 0;
    }
    if ((hourRight == 0) || (secondsPieceNumberHourRight >= standardNinesNbPieces[hourRight]))
    {
      pieceNumberHourRight = 0;
    }
    if ((minuteLeft == 0) || (secondsPieceNumberMinuteLeft >= standardSixNbPieces[minuteLeft]))
    {
      pieceNumberMinuteLeft = 0;
    }
    if ((minuteRight == 0) || (secondsPieceNumberMinuteRight >= standardNinesNbPieces[minuteRight]))
    {
      pieceNumberMinuteRight = 0;
    } 
  }
  
  ledsBegin();
  
  /*Serial.print("piece HourR: ");
  Serial.print((unsigned int)pieceNumberHourRight);
  Serial.print(" piece MinuteR: ");
  Serial.println((unsigned int)pieceNumberMinuteRight);*/
  
  secondsGenericDisplay2(1,  minuteRight, secondRight, secondsNines,  standardNinesSize,  luminosity, secondsColorMinuteRight, secondsColorHourRight);
  secondsGenericDisplay2(10, minuteLeft,  secondLeft,  secondsSix,    standardSixSize,    luminosity, secondsColorMinuteLeft,  secondsColorHourLeft);
  
  /*if (!secondsToggle)
  {
    secondsToggle = true;
    secondsGenericDisplay(1, minuteRight,   0,   standardNines,  standardNinesSize, luminosity, secondsColorMinuteRight);
    secondsGenericDisplay(10, minuteLeft,   0,   standardSix,    standardSixSize,   luminosity, secondsColorMinuteLeft);
  }
  else
  {
    secondsToggle = false;
    secondsGenericDisplay(1, secondRight,   0,   standardNines,  standardNinesSize, 8, secondsColorMinuteRight);
    secondsGenericDisplay(10, secondLeft,   0,   standardSix,    standardSixSize,   8, secondsColorMinuteLeft);
  }*/
  
  secondsGenericDisplay(16, hourRight,   pieceNumberHourRight,   standardNines,  standardNinesSize,  luminosity, secondsColorHourRight);
  secondsGenericDisplay(25, hourLeft,    pieceNumberHourLeft,    standardThrees, standardThreesSize, luminosity, secondsColorHourLeft);
  
  ledsEnd();
  
  return 1000;
}

// ledStartNumber: number of the first LED of the group to update
// value: value of the digit to display
// pieceNumber: number of the variant chosen for the digit
// pieces: array of variant ordered per digit
// piecesSize: size of the pieces
// h, s, l: HSL color used to display the piece
void secondsGenericDisplay(uint8_t ledStartNumber, uint8_t value, uint8_t pieceNumber, const uint8_t ** pieces, uint8_t piecesSize, uint8_t luminosity, uint8_t color)
{  
  for (uint8_t ledOffset=0; ledOffset < piecesSize; ledOffset++)
  {
    uint8_t led_active = pgm_read_byte_near(pieces[value] + piecesSize*pieceNumber + ledOffset);
    
    if (led_active)
    {
      ledsSetColor(ledStartNumber + ledOffset, color*8, 255, luminosity);
    }
    else
    {
      ledsSetColor(ledStartNumber + ledOffset, 0, 0, 0);
    } 
  }
}

void secondsGenericDisplay2(uint8_t ledStartNumber, uint8_t value, uint8_t value2, const uint8_t * pieces, uint8_t piecesSize, uint8_t luminosity, uint8_t color, uint8_t color2)
{  
  for (uint8_t ledOffset=0; ledOffset < piecesSize; ledOffset++)
  {
    uint8_t led_active = pgm_read_byte_near(pieces + value*piecesSize + ledOffset);
    uint8_t led_active2 = pgm_read_byte_near(pieces + value2*piecesSize + ledOffset);
    
    if (led_active && (!led_active2))
    {
      ledsSetColor(ledStartNumber + ledOffset, color*8, 255, luminosity);
    }
    else if ((!led_active) && (led_active2))
    {
      ledsSetColor(ledStartNumber + ledOffset, color*8, 0, 8);
    }
    else if ((led_active) && (led_active2))
    {
      ledsSetColor(ledStartNumber + ledOffset, color*8, 160, luminosity);
    }
    else
    {
      ledsSetColor(ledStartNumber + ledOffset, 0, 0, 0);
    } 
  }
}
