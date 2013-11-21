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
// Standard Mode with Tetris-like display
//----------------------------------------------------------------------------------------
#include "JIXLEDS.h"
#include "JIXStandardConstants.h"
#include "JIXStandardMode.h"

//----------------------------------------------------------------------------------------
// Private functions
//----------------------------------------------------------------------------------------

void standardGenericDisplay(uint8_t ledStartNumber, 
                            uint8_t value, 
                            uint8_t pieceNumber, 
                            const uint8_t ** pieces, 
                            uint8_t piecesSize, 
                            uint8_t h, 
                            uint8_t s, 
                            uint8_t l);

//----------------------------------------------------------------------------------------
// Variables (to store current state of pieces for hold mode)
//----------------------------------------------------------------------------------------
uint8_t standardPieceNumberHourLeft    = 0;
uint8_t standardPieceNumberHourRight   = 0;
uint8_t standardPieceNumberMinuteLeft  = 0;
uint8_t standardPieceNumberMinuteRight = 0;
  
uint8_t standardColorHourLeft     = 0;   
uint8_t standardColorHourRight    = 0;  
uint8_t standardColorMinuteLeft   = 0; 
uint8_t standardColorMinuteRight  = 0;

//----------------------------------------------------------------------------------------
// Public API Implementation
//----------------------------------------------------------------------------------------

unsigned int standardModeFast(uint8_t hourLeft, 
                              uint8_t hourRight, 
                              uint8_t minuteLeft, 
                              uint8_t minuteRight, 
                              uint8_t secondLeft, 
                              uint8_t secondRight, 
                              uint8_t luminosity,
                              bool    hold)
{
  standardMode(hourLeft, hourRight, minuteLeft, minuteRight, secondLeft, secondRight, luminosity, hold);
  return 1000;
}

unsigned int standardModeMedium(uint8_t hourLeft, 
                                uint8_t hourRight, 
                                uint8_t minuteLeft, 
                                uint8_t minuteRight, 
                                uint8_t secondLeft, 
                                uint8_t secondRight, 
                                uint8_t luminosity,
                                bool    hold)
{
  standardMode(hourLeft, hourRight, minuteLeft, minuteRight, secondLeft, secondRight, luminosity, hold);
  return 10000;
}

unsigned int standardModeSlow(uint8_t hourLeft, 
                              uint8_t hourRight, 
                              uint8_t minuteLeft, 
                              uint8_t minuteRight, 
                              uint8_t secondLeft, 
                              uint8_t secondRight, 
                              uint8_t luminosity,
                              bool    hold)
{
  standardMode(hourLeft, hourRight, minuteLeft, minuteRight, secondLeft, secondRight, luminosity, hold);
  return 60000;
}
                          
void standardMode(uint8_t hourLeft, 
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
  
  if (!hold)
  {
    standardPieceNumberHourLeft    = random(standardThreesNbPieces[hourLeft]);
    standardPieceNumberHourRight   = random(standardNinesNbPieces[hourRight]);
    standardPieceNumberMinuteLeft  = random(standardSixNbPieces[minuteLeft]);
    standardPieceNumberMinuteRight = random(standardNinesNbPieces[minuteRight]);
    
    standardColorHourLeft = random(33);
    do { standardColorHourRight   = random(33); } while (abs(standardColorHourLeft - standardColorHourRight) < standardColorDifference);
    do { standardColorMinuteLeft  = random(33); } while ((abs(standardColorHourLeft - standardColorMinuteLeft) < standardColorDifference) ||
                                                 (abs(standardColorHourRight - standardColorMinuteLeft) < standardColorDifference));
    do { standardColorMinuteRight = random(33); } while ((abs(standardColorHourLeft - standardColorMinuteRight) < standardColorDifference)  ||
                                                 (abs(standardColorHourRight - standardColorMinuteRight) < standardColorDifference) ||
                                                 (abs(standardColorMinuteLeft - standardColorMinuteRight) < standardColorDifference));
                                                 
    pieceNumberHourLeft    = standardPieceNumberHourLeft;
    pieceNumberHourRight   = standardPieceNumberHourRight;
    pieceNumberMinuteLeft  = standardPieceNumberMinuteLeft;
    pieceNumberMinuteRight = standardPieceNumberMinuteRight;
  }
  else
  {
    pieceNumberHourLeft    = standardPieceNumberHourLeft;
    pieceNumberHourRight   = standardPieceNumberHourRight;
    pieceNumberMinuteLeft  = standardPieceNumberMinuteLeft;
    pieceNumberMinuteRight = standardPieceNumberMinuteRight;
    
    if ((hourLeft == 0) || (standardPieceNumberHourLeft >= standardThreesNbPieces[hourLeft]))
    {
      pieceNumberHourLeft = 0;
    }
    if ((hourRight == 0) || (standardPieceNumberHourRight >= standardNinesNbPieces[hourRight]))
    {
      pieceNumberHourRight = 0;
    }
    if ((minuteLeft == 0) || (standardPieceNumberMinuteLeft >= standardSixNbPieces[minuteLeft]))
    {
      pieceNumberMinuteLeft = 0;
    }
    if ((minuteRight == 0) || (standardPieceNumberMinuteRight >= standardNinesNbPieces[minuteRight]))
    {
      pieceNumberMinuteRight = 0;
    } 
  }  
  
  ledsBegin();
  
  /*Serial.print("piece HourR: ");
  Serial.print((unsigned int)standardPieceNumberHourRight);
  Serial.print(" piece MinuteR: ");
  Serial.println((unsigned int)standardPieceNumberMinuteRight);*/
  
  standardGenericDisplay(1,  minuteRight, pieceNumberMinuteRight, standardNines,  standardNinesSize,  standardColorMinuteRight*8, (standardColorMinuteRight < 32) ? 255 : 0, luminosity);
  standardGenericDisplay(10, minuteLeft,  pieceNumberMinuteLeft,  standardSix,    standardSixSize,    standardColorMinuteLeft*8,  (standardColorMinuteLeft < 32) ? 255 : 0, luminosity);
  standardGenericDisplay(16, hourRight,   pieceNumberHourRight,   standardNines,  standardNinesSize,  standardColorHourRight*8,   (standardColorHourRight < 32) ? 255 : 0, luminosity);
  standardGenericDisplay(25, hourLeft,    pieceNumberHourLeft,    standardThrees, standardThreesSize, standardColorHourLeft*8,    (standardColorHourLeft < 32) ? 255 : 0, luminosity);
  
  ledsEnd();
}

// ledStartNumber: number of the first LED of the group to update
// value: value of the digit to display
// pieceNumber: number of the variant chosen for the digit
// pieces: array of variant ordered per digit
// piecesSize: size of the pieces
// h, s, l: HSL color used to display the piece
void standardGenericDisplay(uint8_t ledStartNumber, uint8_t value, uint8_t pieceNumber, const uint8_t ** pieces, uint8_t piecesSize, uint8_t h, uint8_t s, uint8_t l)
{
  for (uint8_t ledOffset=0; ledOffset < piecesSize; ledOffset++)
  {
    uint8_t led_active = pgm_read_byte_near(pieces[value] + piecesSize*pieceNumber + ledOffset);
    
    if (led_active)
      ledsSetColor(ledStartNumber + ledOffset, h, s, l);
    else
      ledsSetColor(ledStartNumber + ledOffset, 0, 0, 0);
  }
}

