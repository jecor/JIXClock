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
// Colorful Mode with Tetris-like display
//----------------------------------------------------------------------------------------
#include "JIXLEDS.h"
#include "JIXColorfulMode.h"
#include "JIXStandardConstants.h"

//----------------------------------------------------------------------------------------
// Internal functions
//----------------------------------------------------------------------------------------
 
void colorfulMode(uint8_t hourLeft, 
                  uint8_t hourRight, 
                  uint8_t minuteLeft, 
                  uint8_t minuteRight, 
                  uint8_t secondLeft, 
                  uint8_t secondRight, 
                  uint8_t luminosity,
                  bool    hold);

void colorfulGenericDisplay(uint8_t ledStartNumber, 
                            uint8_t value, 
                            uint8_t pieceNumber, 
                            const uint8_t ** pieces, 
                            uint8_t piecesSize, 
                            uint8_t luminosity, 
                            uint8_t color);

//----------------------------------------------------------------------------------------
// Externs
//----------------------------------------------------------------------------------------

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
uint8_t colorfulPieceNumberHourLeft;
uint8_t colorfulPieceNumberHourRight;
uint8_t colorfulPieceNumberMinuteLeft;
uint8_t colorfulPieceNumberMinuteRight;

uint8_t colorfulColorMinuteLeft;
uint8_t colorfulColorMinuteRight;
uint8_t colorfulColorHourLeft;
uint8_t colorfulColorHourRight;

//----------------------------------------------------------------------------------------
// Public API Implementation
//----------------------------------------------------------------------------------------

unsigned int colorfulModeFast(uint8_t hourLeft, 
                              uint8_t hourRight, 
                              uint8_t minuteLeft, 
                              uint8_t minuteRight, 
                              uint8_t secondLeft, 
                              uint8_t secondRight, 
                              uint8_t luminosity,
                              bool    hold)
{
  colorfulMode(hourLeft, hourRight, minuteLeft, minuteRight, secondLeft, secondRight, luminosity, hold);
  
  return 1000;
}  

unsigned int colorfulModeMedium(uint8_t hourLeft, 
                                uint8_t hourRight, 
                                uint8_t minuteLeft, 
                                uint8_t minuteRight, 
                                uint8_t secondLeft, 
                                uint8_t secondRight, 
                                uint8_t luminosity,
                                bool    hold)
{
  colorfulMode(hourLeft, hourRight, minuteLeft, minuteRight, secondLeft, secondRight, luminosity, hold);
  
  return 10000;
} 

unsigned int colorfulModeSlow(uint8_t hourLeft, 
                              uint8_t hourRight, 
                              uint8_t minuteLeft, 
                              uint8_t minuteRight, 
                              uint8_t secondLeft, 
                              uint8_t secondRight, 
                              uint8_t luminosity,
                              bool    hold)
{
  colorfulMode(hourLeft, hourRight, minuteLeft, minuteRight, secondLeft, secondRight, luminosity, hold);
  
  return 60000;
} 


void colorfulMode(uint8_t hourLeft, 
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
    colorfulPieceNumberHourLeft    = random(standardThreesNbPieces[hourLeft]);
    colorfulPieceNumberHourRight   = random(standardNinesNbPieces[hourRight]);
    colorfulPieceNumberMinuteLeft  = random(standardSixNbPieces[minuteLeft]);
    colorfulPieceNumberMinuteRight = random(standardNinesNbPieces[minuteRight]);
    
    colorfulColorHourLeft = random(33);
    do { colorfulColorHourRight   = random(33); } while (abs(colorfulColorHourLeft - colorfulColorHourRight) < standardColorDifference);
    do { colorfulColorMinuteLeft  = random(33); } while ((abs(colorfulColorHourLeft - colorfulColorMinuteLeft) < standardColorDifference) ||
                                                         (abs(colorfulColorHourRight - colorfulColorMinuteLeft) < standardColorDifference));
    do { colorfulColorMinuteRight = random(33); } while ((abs(colorfulColorHourLeft - colorfulColorMinuteRight) < standardColorDifference)  ||
                                                 (abs(colorfulColorHourRight - colorfulColorMinuteRight) < standardColorDifference) ||
                                                 (abs(colorfulColorMinuteLeft - colorfulColorMinuteRight) < standardColorDifference));  
                                                 
    pieceNumberHourLeft    = colorfulPieceNumberHourLeft;
    pieceNumberHourRight   = colorfulPieceNumberHourRight;
    pieceNumberMinuteLeft  = colorfulPieceNumberMinuteLeft;
    pieceNumberMinuteRight = colorfulPieceNumberMinuteRight;
  }
  else
  {
    pieceNumberHourLeft    = colorfulPieceNumberHourLeft;
    pieceNumberHourRight   = colorfulPieceNumberHourRight;
    pieceNumberMinuteLeft  = colorfulPieceNumberMinuteLeft;
    pieceNumberMinuteRight = colorfulPieceNumberMinuteRight;
    
    if ((hourLeft == 0) || (colorfulPieceNumberHourLeft >= standardThreesNbPieces[hourLeft]))
    {
      pieceNumberHourLeft = 0;
    }
    if ((hourRight == 0) || (colorfulPieceNumberHourRight >= standardNinesNbPieces[hourRight]))
    {
      pieceNumberHourRight = 0;
    }
    if ((minuteLeft == 0) || (colorfulPieceNumberMinuteLeft >= standardSixNbPieces[minuteLeft]))
    {
      pieceNumberMinuteLeft = 0;
    }
    if ((minuteRight == 0) || (colorfulPieceNumberMinuteRight >= standardNinesNbPieces[minuteRight]))
    {
      pieceNumberMinuteRight = 0;
    } 
  }
  
  ledsBegin();
  
  /*Serial.print("piece HourR: ");
  Serial.print((unsigned int)pieceNumberHourRight);
  Serial.print(" piece MinuteR: ");
  Serial.println((unsigned int)pieceNumberMinuteRight);*/
  
  colorfulGenericDisplay(1,  minuteRight, pieceNumberMinuteRight, standardNines,  standardNinesSize,  luminosity, colorfulColorMinuteRight);
  colorfulGenericDisplay(10, minuteLeft,  pieceNumberMinuteLeft,  standardSix,    standardSixSize,    luminosity, colorfulColorMinuteLeft);
  colorfulGenericDisplay(16, hourRight,   pieceNumberHourRight,   standardNines,  standardNinesSize,  luminosity, colorfulColorHourRight);
  colorfulGenericDisplay(25, hourLeft,    pieceNumberHourLeft,    standardThrees, standardThreesSize, luminosity, colorfulColorHourLeft);
  
  ledsEnd();
}

// ledStartNumber: number of the first LED of the group to update
// value: value of the digit to display
// pieceNumber: number of the variant chosen for the digit
// pieces: array of variant ordered per digit
// piecesSize: size of the pieces
// h, s, l: HSL color used to display the piece
void colorfulGenericDisplay(uint8_t ledStartNumber, uint8_t value, uint8_t pieceNumber, const uint8_t ** pieces, uint8_t piecesSize, uint8_t luminosity, uint8_t color)
{  
  for (uint8_t ledOffset=0; ledOffset < piecesSize; ledOffset++)
  {
    uint8_t led_active = pgm_read_byte_near(pieces[value] + piecesSize*pieceNumber + ledOffset);
    
    if (led_active)
    {
      ledsSetColor(ledStartNumber + ledOffset, color*8, (color < 32) ? 255 : 0, luminosity);
      
      color += 3;
      color %= 32;
    }
    else
    {
      ledsSetColor(ledStartNumber + ledOffset, 0, 0, 0);
    } 
  }
}
