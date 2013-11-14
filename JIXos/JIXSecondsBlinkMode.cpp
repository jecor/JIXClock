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
#include "JIXSecondsBlinkMode.h"

//----------------------------------------------------------------------------------------
// Externs
//----------------------------------------------------------------------------------------

// TODO: fix this
void secondsGenericDisplay(uint8_t ledStartNumber, uint8_t value, uint8_t pieceNumber, const uint8_t ** pieces, uint8_t piecesSize, uint8_t luminosity, uint8_t color);


extern const unsigned int standardThreesSize;
extern const unsigned int standardSixSize;
extern const unsigned int standardNinesSize;
extern const uint8_t * standardThrees[];
extern const uint8_t * standardSix[];
extern const uint8_t * standardNines[];
extern const uint8_t standardThreesNbPieces[];
extern const uint8_t standardSixNbPieces[];
extern const uint8_t standardNinesNbPieces[];
extern const uint8_t standardColorDifference;

//----------------------------------------------------------------------------------------
// Variables (to store current state of pieces for hold mode)
//----------------------------------------------------------------------------------------
uint8_t secondsBlinkPieceNumberHourLeft;
uint8_t secondsBlinkPieceNumberHourRight;
uint8_t secondsBlinkPieceNumberMinuteLeft;
uint8_t secondsBlinkPieceNumberMinuteRight;

uint8_t secondsBlinkColorHourLeft;
uint8_t secondsBlinkColorHourRight;
uint8_t secondsBlinkColorMinuteLeft;
uint8_t secondsBlinkColorMinuteRight;

bool secondsBlinkToggle = false;

//----------------------------------------------------------------------------------------
// Public API Implementation
//----------------------------------------------------------------------------------------

unsigned int secondsBlinkMode(uint8_t hourLeft, 
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
  
  if (!hold && !secondsBlinkToggle)
  {
    secondsBlinkPieceNumberHourLeft    = random(standardThreesNbPieces[hourLeft]);
    secondsBlinkPieceNumberHourRight   = random(standardNinesNbPieces[hourRight]);
    secondsBlinkPieceNumberMinuteLeft  = random(standardSixNbPieces[minuteLeft]);
    secondsBlinkPieceNumberMinuteRight = random(standardNinesNbPieces[minuteRight]);
    
    secondsBlinkColorHourLeft = random(32);
    do { secondsBlinkColorHourRight   = random(32); } while (abs(secondsBlinkColorHourLeft - secondsBlinkColorHourRight) < standardColorDifference);
    
    if ((secondLeft == 0) && (secondRight == 0))
    {
      do { secondsBlinkColorMinuteLeft  = random(32); } while ((abs(secondsBlinkColorHourLeft - secondsBlinkColorMinuteLeft) < standardColorDifference) ||
                                                           (abs(secondsBlinkColorHourRight - secondsBlinkColorMinuteLeft) < standardColorDifference));
      do { secondsBlinkColorMinuteRight = random(32); } while ((abs(secondsBlinkColorHourLeft - secondsBlinkColorMinuteRight) < standardColorDifference)  ||
                                                   (abs(secondsBlinkColorHourRight - secondsBlinkColorMinuteRight) < standardColorDifference) ||
                                                   (abs(secondsBlinkColorMinuteLeft - secondsBlinkColorMinuteRight) < standardColorDifference));  
    }
                                                 
    pieceNumberHourLeft    = secondsBlinkPieceNumberHourLeft;
    pieceNumberHourRight   = secondsBlinkPieceNumberHourRight;
    pieceNumberMinuteLeft  = secondsBlinkPieceNumberMinuteLeft;
    pieceNumberMinuteRight = secondsBlinkPieceNumberMinuteRight;
  }
  else
  {
    pieceNumberHourLeft    = secondsBlinkPieceNumberHourLeft;
    pieceNumberHourRight   = secondsBlinkPieceNumberHourRight;
    pieceNumberMinuteLeft  = secondsBlinkPieceNumberMinuteLeft;
    pieceNumberMinuteRight = secondsBlinkPieceNumberMinuteRight;
    
    if ((hourLeft == 0) || (secondsBlinkPieceNumberHourLeft >= standardThreesNbPieces[hourLeft]))
    {
      pieceNumberHourLeft = 0;
    }
    if ((hourRight == 0) || (secondsBlinkPieceNumberHourRight >= standardNinesNbPieces[hourRight]))
    {
      pieceNumberHourRight = 0;
    }
    if ((minuteLeft == 0) || (secondsBlinkPieceNumberMinuteLeft >= standardSixNbPieces[minuteLeft]))
    {
      pieceNumberMinuteLeft = 0;
    }
    if ((minuteRight == 0) || (secondsBlinkPieceNumberMinuteRight >= standardNinesNbPieces[minuteRight]))
    {
      pieceNumberMinuteRight = 0;
    } 
  }
  
  ledsBegin();
  
  if ((!secondsBlinkToggle) || hold)
  {
    secondsBlinkToggle = true;
    secondsGenericDisplay(1, minuteRight,   0,   standardNines,  standardNinesSize, luminosity, secondsBlinkColorMinuteRight);
    secondsGenericDisplay(10, minuteLeft,   0,   standardSix,    standardSixSize,   luminosity, secondsBlinkColorMinuteLeft);
  }
  else
  {
    secondsBlinkToggle = false;
    secondsGenericDisplay(1, secondRight,   0,   standardNines,  standardNinesSize, 8, secondsBlinkColorMinuteRight);
    secondsGenericDisplay(10, secondLeft,   0,   standardSix,    standardSixSize,   8, secondsBlinkColorMinuteLeft);
  }
  
  secondsGenericDisplay(16, hourRight,   pieceNumberHourRight,   standardNines,  standardNinesSize,  luminosity, secondsBlinkColorHourRight);
  secondsGenericDisplay(25, hourLeft,    pieceNumberHourLeft,    standardThrees, standardThreesSize, luminosity, secondsBlinkColorHourLeft);
  
  ledsEnd();
  
  return 500;
}


