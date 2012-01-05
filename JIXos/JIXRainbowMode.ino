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
// Rainbow Mode with Tetris-like display
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// Public API
//----------------------------------------------------------------------------------------

unsigned int rainbowModeFast(uint8_t hourLeft, 
                             uint8_t hourRight, 
                             uint8_t minuteLeft, 
                             uint8_t minuteRight, 
                             uint8_t secondLeft, 
                             uint8_t secondRight, 
                             uint8_t luminosity,
                             bool    hold);

unsigned int rainbowModeMedium(uint8_t hourLeft, 
                               uint8_t hourRight, 
                               uint8_t minuteLeft, 
                               uint8_t minuteRight, 
                               uint8_t secondLeft, 
                               uint8_t secondRight, 
                               uint8_t luminosity,
                               bool    hold);

unsigned int rainbowModeSlow(uint8_t hourLeft, 
                             uint8_t hourRight, 
                             uint8_t minuteLeft, 
                             uint8_t minuteRight, 
                             uint8_t secondLeft, 
                             uint8_t secondRight, 
                             uint8_t luminosity,
                             bool    hold);                     
                         
void rainbowMode(uint8_t hourLeft, 
                 uint8_t hourRight, 
                 uint8_t minuteLeft, 
                 uint8_t minuteRight, 
                 uint8_t secondLeft, 
                 uint8_t secondRight, 
                 uint8_t luminosity,
                 bool    hold);

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


uint8_t rainbowPieceNumberHourLeft = 0;   
uint8_t rainbowPieceNumberHourRight = 0;  
uint8_t rainbowPieceNumberMinuteLeft = 0; 
uint8_t rainbowPieceNumberMinuteRight = 0;

uint8_t rainbowColorHourLeft = 0;   
uint8_t rainbowColorHourRight = 0;  
uint8_t rainbowColorMinuteLeft = 0; 
uint8_t rainbowColorMinuteRight = 0;

unsigned int rainbowCounter = 0;

//----------------------------------------------------------------------------------------
// Public API Implementation
//----------------------------------------------------------------------------------------

unsigned int rainbowModeFast(uint8_t hourLeft, 
                             uint8_t hourRight, 
                             uint8_t minuteLeft, 
                             uint8_t minuteRight, 
                             uint8_t secondLeft, 
                             uint8_t secondRight, 
                             uint8_t luminosity,
                             bool    hold)
{
  rainbowMode(hourLeft, hourRight, minuteLeft, minuteRight, secondLeft, secondRight, luminosity, hold);
  
  return 10;
}  
                         
unsigned int rainbowModeMedium(uint8_t hourLeft, 
                               uint8_t hourRight, 
                               uint8_t minuteLeft, 
                               uint8_t minuteRight, 
                               uint8_t secondLeft, 
                               uint8_t secondRight, 
                               uint8_t luminosity,
                               bool    hold)
{
  rainbowMode(hourLeft, hourRight, minuteLeft, minuteRight, secondLeft, secondRight, luminosity, hold);
  
  return 100;
}  

unsigned int rainbowModeSlow(uint8_t hourLeft, 
                             uint8_t hourRight, 
                             uint8_t minuteLeft, 
                             uint8_t minuteRight, 
                             uint8_t secondLeft, 
                             uint8_t secondRight, 
                             uint8_t luminosity,
                             bool    hold)
{
  rainbowMode(hourLeft, hourRight, minuteLeft, minuteRight, secondLeft, secondRight, luminosity, hold);
  
  return 1000;
}  


void rainbowMode(uint8_t hourLeft, 
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
    if ((rainbowColorHourLeft == 0) &&
        (rainbowColorHourRight == 0) &&
        (rainbowColorMinuteLeft == 0) &&
        (rainbowColorMinuteRight == 0))
    {
      rainbowColorHourLeft = random(256);
      do { rainbowColorHourRight   = random(256); } while (abs(rainbowColorHourLeft - rainbowColorHourRight) < standardColorDifference);
      do { rainbowColorMinuteLeft  = random(256); } while ((abs(rainbowColorHourLeft - rainbowColorMinuteLeft) < standardColorDifference) ||
                                                    (abs(rainbowColorHourRight - rainbowColorMinuteLeft) < standardColorDifference));
      do { rainbowColorMinuteRight = random(256); } while ((abs(rainbowColorHourLeft - rainbowColorMinuteRight) < standardColorDifference)  ||
                                                    (abs(rainbowColorHourRight - rainbowColorMinuteRight) < standardColorDifference) ||
                                                    (abs(rainbowColorMinuteLeft - rainbowColorMinuteRight) < standardColorDifference));
                                                    
      rainbowPieceNumberHourLeft    = random(standardThreesNbPieces[hourLeft]);
      rainbowPieceNumberHourRight   = random(standardNinesNbPieces[hourRight]);
      rainbowPieceNumberMinuteLeft  = random(standardSixNbPieces[minuteLeft]);
      rainbowPieceNumberMinuteRight = random(standardNinesNbPieces[minuteRight]);
    }
    else
    {
      rainbowColorHourLeft++;    if (rainbowColorHourLeft >= 256) rainbowColorHourLeft = 0;
      rainbowColorHourRight++;   if (rainbowColorHourRight >= 256) rainbowColorHourRight = 0;
      rainbowColorMinuteLeft++;  if (rainbowColorMinuteLeft >= 256) rainbowColorMinuteLeft = 0;
      rainbowColorMinuteRight++; if (rainbowColorMinuteRight >= 256) rainbowColorMinuteRight = 0;
    } 
    
    rainbowCounter++;
    if (rainbowCounter >= 200)
    {
      rainbowPieceNumberHourLeft    = random(standardThreesNbPieces[hourLeft]);
      rainbowPieceNumberHourRight   = random(standardNinesNbPieces[hourRight]);
      rainbowPieceNumberMinuteLeft  = random(standardSixNbPieces[minuteLeft]);
      rainbowPieceNumberMinuteRight = random(standardNinesNbPieces[minuteRight]);
      
      rainbowCounter = 0;
    }
    
    pieceNumberHourLeft    = rainbowPieceNumberHourLeft;
    pieceNumberHourRight   = rainbowPieceNumberHourRight;
    pieceNumberMinuteLeft  = rainbowPieceNumberMinuteLeft;
    pieceNumberMinuteRight = rainbowPieceNumberMinuteRight;
  }
  else
  {
    pieceNumberHourLeft    = rainbowPieceNumberHourLeft;
    pieceNumberHourRight   = rainbowPieceNumberHourRight;
    pieceNumberMinuteLeft  = rainbowPieceNumberMinuteLeft;
    pieceNumberMinuteRight = rainbowPieceNumberMinuteRight;
    
    if ((hourLeft == 0) || (rainbowPieceNumberHourLeft >= standardThreesNbPieces[hourLeft]))
    {
      pieceNumberHourLeft = 0;
    }
    if ((hourRight == 0) || (rainbowPieceNumberHourRight >= standardNinesNbPieces[hourRight]))
    {
      pieceNumberHourRight = 0;
    }
    if ((minuteLeft == 0) || (rainbowPieceNumberMinuteLeft >= standardSixNbPieces[minuteLeft]))
    {
      pieceNumberMinuteLeft = 0;
    }
    if ((minuteRight == 0) || (rainbowPieceNumberMinuteRight >= standardNinesNbPieces[minuteRight]))
    {
      pieceNumberMinuteRight = 0;
    } 
  }
  
  ledsBegin();
  
  /*Serial.print("piece HourR: ");
  Serial.print((unsigned int)pieceNumberHourRight);
  Serial.print(" piece MinuteR: ");
  Serial.println((unsigned int)pieceNumberMinuteRight);*/
  
  rainbowGenericDisplay(1,  minuteRight, pieceNumberMinuteRight, standardNines,  standardNinesSize,  rainbowColorMinuteRight, luminosity);
  rainbowGenericDisplay(10, minuteLeft,  pieceNumberMinuteLeft,  standardSix,    standardSixSize,    rainbowColorMinuteLeft, luminosity);
  rainbowGenericDisplay(16, hourRight,   pieceNumberHourRight,   standardNines,  standardNinesSize,  rainbowColorHourRight, luminosity);
  rainbowGenericDisplay(25, hourLeft,    pieceNumberHourLeft,    standardThrees, standardThreesSize, rainbowColorHourLeft, luminosity);
  
  ledsEnd();
}

// ledStartNumber: number of the first LED of the group to update
// value: value of the digit to display
// pieceNumber: number of the variant chosen for the digit
// pieces: array of variant ordered per digit
// piecesSize: size of the pieces
// h, s, l: HSL color used to display the piece
void rainbowGenericDisplay(uint8_t ledStartNumber, uint8_t value, uint8_t pieceNumber, const uint8_t ** pieces, uint8_t piecesSize, uint8_t h, uint8_t luminosity)
{  
  for (uint8_t ledOffset=0; ledOffset < piecesSize; ledOffset++)
  {
    uint8_t led_active = pgm_read_byte_near(pieces[value] + piecesSize*pieceNumber + ledOffset);
    
    if (led_active)
    {
      ledsSetColor(ledStartNumber + ledOffset, h, 255, luminosity);
    }
    else
    {
      ledsSetColor(ledStartNumber + ledOffset, 0, 0, 0);
    } 
  }
}
