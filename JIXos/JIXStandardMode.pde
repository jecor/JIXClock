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

//----------------------------------------------------------------------------------------
// Public API
//----------------------------------------------------------------------------------------

unsigned int standardModeFast(uint8_t hourLeft, 
                              uint8_t hourRight, 
                              uint8_t minuteLeft, 
                              uint8_t minuteRight, 
                              uint8_t secondLeft, 
                              uint8_t secondRight, 
                              uint8_t luminosity,
                              bool    hold);
                          
unsigned int standardModeMedium(uint8_t hourLeft, 
                                uint8_t hourRight, 
                                uint8_t minuteLeft, 
                                uint8_t minuteRight, 
                                uint8_t secondLeft, 
                                uint8_t secondRight, 
                                uint8_t luminosity,
                                bool    hold);
                          
unsigned int standardModeSlow(uint8_t hourLeft, 
                              uint8_t hourRight, 
                              uint8_t minuteLeft, 
                              uint8_t minuteRight, 
                              uint8_t secondLeft, 
                              uint8_t secondRight, 
                              uint8_t luminosity,
                              bool    hold);
                          
void standardMode(uint8_t hourLeft, 
                  uint8_t hourRight, 
                  uint8_t minuteLeft, 
                  uint8_t minuteRight, 
                  uint8_t secondLeft, 
                  uint8_t secondRight, 
                  uint8_t luminosity,
                  bool    hold);

//----------------------------------------------------------------------------------------
// Constants
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// Constants for 3 LEDs displays
//----------------------------------------------------------------------------------------

const unsigned int standardThreesSize  = 3;

//----------------------------------------------------------------------------------------
const uint8_t standardThreesNbPieces0 = 1;

const bool standardThrees0[standardThreesNbPieces0 * standardThreesSize] = 
            { 0,
              0,
              0,  
            };

//----------------------------------------------------------------------------------------
const uint8_t standardThreesNbPieces1 = 3;

const bool standardThrees1[standardThreesNbPieces1 * standardThreesSize] = 
            { 1,
              0,
              0,
            
              0,
              1,
              0,
            
              0,
              0,
              1  
            };
            
//----------------------------------------------------------------------------------------
const uint8_t standardThreesNbPieces2 = 2;

const bool standardThrees2[standardThreesNbPieces2 * standardThreesSize] = 
            { 1,
              1,
              0,
            
              0,
              1,
              1  
            };

//----------------------------------------------------------------------------------------
const bool * standardThrees[3] = { (const bool *)standardThrees0, 
                                   (const bool *)standardThrees1, 
                                   (const bool *)standardThrees2
                                 };
                                   
const uint8_t standardThreesNbPieces[3] = { standardThreesNbPieces0,
                                            standardThreesNbPieces1,
                                            standardThreesNbPieces2
                                          };

//----------------------------------------------------------------------------------------
// Constants for 6 LEDs displays
//----------------------------------------------------------------------------------------

const unsigned int standardSixSize  = 6;

//----------------------------------------------------------------------------------------
const uint8_t standardSixNbPieces0 = 1;

const bool standardSix0[standardSixNbPieces0 * standardSixSize] = 
            { 0, 0,
              0, 0,
              0, 0 
            };

//----------------------------------------------------------------------------------------
const uint8_t standardSixNbPieces1 = 6;

const bool standardSix1[standardSixNbPieces1 * standardSixSize] = 
            { 1, 0,
              0, 0,
              0, 0,
            
              0, 0,
              1, 0,
              0, 0,
            
              0, 0,
              0, 0,
              1, 0,
            
              0, 1,
              0, 0,
              0, 0, 
            
              0, 0,
              0, 1,
              0, 0, 
            
              0, 0,
              0, 0,
              0, 1  
            };
            
//----------------------------------------------------------------------------------------
const uint8_t standardSixNbPieces2 = 9;

const bool standardSix2[standardSixNbPieces2 * standardSixSize] = 
            { 1, 1,
              0, 0,
              0, 0,
              
              0, 0,
              1, 1,
              0, 0,
              
              0, 0,
              0, 0,
              1, 1,
              
              1, 0,
              1, 0,
              0, 0,
              
              0, 1,
              0, 1,
              0, 0,
              
              0, 0,
              1, 0,
              1, 0,
              
              0, 0,
              0, 1,
              0, 1,
              
              1, 0,
              0, 0,
              1, 0,
              
              0, 1,
              0, 0,
              0, 1
            };

//----------------------------------------------------------------------------------------            
const uint8_t standardSixNbPieces3 = 9;

const bool standardSix3[standardSixNbPieces3 * standardSixSize] = 
            { 1, 1,
              1, 0,
              0, 0,
              
              0, 1,
              1, 1,
              0, 0,
              
              0, 0,
              0, 1,
              1, 1,
              
              1, 0,
              1, 0,
              1, 0,
              
              0, 1,
              0, 1,
              0, 1,
              
              0, 0,
              1, 1,
              1, 0,
              
              0, 0,
              1, 1,
              1, 0,
              
              0, 1,
              1, 0,
              1, 0,
              
              0, 1,
              0, 1,
              1, 0
            };
            
//----------------------------------------------------------------------------------------            
const uint8_t standardSixNbPieces4 = 9;

const bool standardSix4[standardSixNbPieces4 * standardSixSize] = 
            { 1, 1,
              1, 1,
              0, 0,
              
              0, 0,
              1, 1,
              1, 1,
              
              0, 1,
              0, 1,
              1, 1,
              
              1, 1,
              1, 0,
              1, 0,
              
              1, 1,
              0, 1,
              0, 1,
              
              1, 0,
              1, 0,
              1, 1,
              
              1, 1,
              0, 0,
              1, 1,
              
              1, 0,
              1, 1,
              1, 0,
              
              0, 1,
              1, 1,
              0, 1
            };
         
//----------------------------------------------------------------------------------------            
const uint8_t standardSixNbPieces5 = 6;

const bool standardSix5[standardSixNbPieces5 * standardSixSize] = 
            { 0, 1,
              1, 1,
              1, 1,
              
              1, 0,
              1, 1,
              1, 1,
              
              1, 1,
              0, 1,
              1, 1,
              
              1, 1,
              1, 0,
              1, 1,
              
              1, 1,
              1, 1,
              0, 1,
              
              1, 1,
              1, 1,
              1, 0
            };      

//----------------------------------------------------------------------------------------
const bool * standardSix[6] = { (const bool *)standardSix0, 
                                (const bool *)standardSix1, 
                                (const bool *)standardSix2,
                                (const bool *)standardSix3,
                                (const bool *)standardSix4,
                                (const bool *)standardSix5
                                 };
                                   
const uint8_t standardSixNbPieces[6] = { standardSixNbPieces0,
                                         standardSixNbPieces1,
                                         standardSixNbPieces2,
                                         standardSixNbPieces3,
                                         standardSixNbPieces4,
                                         standardSixNbPieces5
                                       };
                                           
//----------------------------------------------------------------------------------------
// Constants for 9 LEDs displays
//----------------------------------------------------------------------------------------

const unsigned int standardNinesSize  = 9;

//----------------------------------------------------------------------------------------
const uint8_t standardNinesNbPieces0 = 1;

const bool standardNines0[standardNinesNbPieces0 * standardNinesSize] = 
            { 0, 0, 0,
              0, 0, 0,
              0, 0, 0  
            };

//----------------------------------------------------------------------------------------                        
const uint8_t standardNinesNbPieces1 = 9;

const bool standardNines1[standardNinesNbPieces1 * standardNinesSize] = 
            { 1, 0, 0,
              0, 0, 0,
              0, 0, 0,
              
              0, 1, 0,
              0, 0, 0,
              0, 0, 0,
              
              0, 0, 1,
              0, 0, 0,
              0, 0, 0,
              
              0, 0, 0,
              1, 0, 0,
              0, 0, 0,
              
              0, 0, 0,
              0, 1, 0,
              0, 0, 0,
              
              0, 0, 0,
              0, 0, 1,
              0, 0, 0,
              
              0, 0, 0,
              0, 0, 0,
              1, 0, 0,
              
              0, 0, 0,
              0, 0, 0,
              0, 1, 0,
              
              0, 0, 0,
              0, 0, 0,
              0, 0, 1  
            };
                        
//----------------------------------------------------------------------------------------
const uint8_t standardNinesNbPieces2 = 9;

const bool standardNines2[standardNinesNbPieces1 * standardNinesSize] = 
            { 1, 1, 0,
              0, 0, 0,
              0, 0, 0,
              
              0, 1, 1,
              0, 0, 0,
              0, 0, 0,
              
              0, 0, 1,
              0, 1, 0,
              0, 0, 0,
              
              0, 0, 0,
              1, 0, 0,
              1, 0, 0,
              
              0, 0, 0,
              0, 1, 0,
              0, 0, 1,
              
              0, 0, 0,
              0, 0, 1,
              0, 0, 1,
              
              0, 0, 0,
              0, 0, 0,
              1, 1, 0,
              
              0, 0, 0,
              0, 1, 0,
              0, 1, 0,
              
              0, 1, 0,
              0, 1, 0,
              0, 0, 0  
            };
              
//----------------------------------------------------------------------------------------
const uint8_t standardNinesNbPieces3 = 9;

const bool standardNines3[standardNinesNbPieces3 * standardNinesSize] = 
            { 1, 1, 1,
              0, 0, 0,
              0, 0, 0,
              
              0, 0, 0,
              1, 1, 1,
              0, 0, 0,
              
              0, 0, 0,
              0, 0, 0,
              1, 1, 1,
              
              1, 0, 0,
              1, 0, 0,
              1, 0, 0,
              
              0, 1, 0,
              0, 1, 0,
              0, 1, 0,
              
              0, 0, 1,
              0, 0, 1,
              0, 0, 1,
              
              0, 0, 1,
              0, 1, 0,
              1, 0, 0,
              
              1, 0, 0,
              0, 1, 0,
              0, 0, 1,
              
              0, 1, 0,
              1, 1, 0,
              0, 0, 0  
            };

//----------------------------------------------------------------------------------------
const uint8_t standardNinesNbPieces4 = 9;

bool standardNines4[standardNinesNbPieces4 * standardNinesSize] = 
            { 1, 1, 1,
              0, 0, 1,
              0, 0, 0,
              
              1, 1, 1,
              1, 0, 0,
              0, 0, 0,
              
              0, 0, 1,
              0, 0, 1,
              0, 1, 1,
              
              1, 0, 0,
              1, 0, 0,
              1, 1, 0,
              
              0, 0, 0,
              1, 1, 1,
              0, 0, 1,
              
              0, 0, 0,
              0, 0, 1,
              1, 1, 1,
              
              0, 0, 0,
              1, 0, 0,
              1, 1, 1,
              
              1, 1, 0,
              1, 1, 0,
              0, 0, 0,
              
              0, 0, 0,
              0, 1, 1,
              0, 1, 1  
            };

//----------------------------------------------------------------------------------------
const uint8_t standardNinesNbPieces5 = 9;

const bool standardNines5[standardNinesNbPieces5 * standardNinesSize] = 
            { 1, 1, 1,
              0, 1, 0,
              0, 1, 0,
              
              0, 1, 0,
              0, 1, 0,
              1, 1, 1,
              
              1, 0, 1,
              0, 1, 0,
              1, 0, 1,
              
              0, 0, 1,
              1, 1, 1,
              0, 0, 1,
              
              1, 0, 0,
              1, 1, 1,
              1, 0, 0,
              
              0, 0, 1,
              0, 1, 1,
              0, 1, 1,
              
              0, 0, 0,
              0, 1, 1,
              1, 1, 1,
              
              1, 1, 0,
              1, 1, 0,
              0, 1, 0,
              
              0, 1, 0,
              1, 1, 1,
              0, 1, 0  
            };

//----------------------------------------------------------------------------------------
const uint8_t standardNinesNbPieces6 = 7;

const bool standardNines6[standardNinesNbPieces6 * standardNinesSize] = 
            { 1, 1, 1,
              1, 1, 1,
              0, 0, 0,
              
              0, 0, 0,
              1, 1, 1,
              1, 1, 1,
              
              0, 1, 1,
              0, 1, 1,
              0, 1, 1,
              
              1, 1, 0,
              1, 1, 0,
              1, 1, 0,
              
              0, 1, 1,
              1, 1, 1,
              0, 1, 0,
              
              1, 0, 1,
              1, 0, 1,
              1, 0, 1,
              
              1, 1, 1,
              0, 0, 0,
              1, 1, 1 
            };
                  
//----------------------------------------------------------------------------------------
const uint8_t standardNinesNbPieces7 = 14;

const bool standardNines7[standardNinesNbPieces7 * standardNinesSize] = 
            { 1, 1, 1,
              1, 1, 1,
              1, 0, 0,
              
              1, 1, 1,
              1, 1, 1,
              0, 1, 0,
              
              1, 1, 1,
              1, 1, 1,
              0, 0, 1,
              
              1, 0, 0,
              1, 1, 1,
              1, 1, 1,
              
              0, 1, 0,
              1, 1, 1,
              1, 1, 1,
              
              0, 0, 1,
              1, 1, 1,
              1, 1, 1,
              
              1, 1, 1,
              1, 1, 0,
              1, 1, 0,
              
              1, 1, 0,
              1, 1, 1,
              1, 1, 0,
              
              1, 1, 0,
              1, 1, 0,
              1, 1, 1,
             
              1, 1, 1,
              0, 1, 1,
              0, 1, 1,
             
              0, 1, 1,
              1, 1, 1,
              0, 1, 1,
             
              0, 1, 1,
              0, 1, 1,
              1, 1, 1,
             
              1, 0, 1,
              1, 1, 1,
              1, 0, 1,
             
              1, 1, 1,
              0, 1, 0,
              1, 1, 1 
            };

//----------------------------------------------------------------------------------------
const uint8_t standardNinesNbPieces8 = 7;

const bool standardNines8[standardNinesNbPieces8 * standardNinesSize] = 
            { 1, 1, 1,
              1, 1, 1,
              1, 0, 1,
              
              1, 0, 1,
              1, 1, 1,
              1, 1, 1,
              
              1, 1, 1,
              1, 1, 0,
              1, 1, 1,
              
              1, 1, 1,
              0, 1, 1,
              1, 1, 1,
              
              1, 1, 1,
              1, 0, 1,
              1, 1, 1,
              
              1, 1, 1,
              1, 1, 1,
              0, 1, 1,
              
              1, 1, 1,
              1, 1, 1,
              1, 1, 0  
            };

//----------------------------------------------------------------------------------------
const uint8_t standardNinesNbPieces9 = 1;

const bool standardNines9[standardNinesNbPieces8 * standardNinesSize] = 
            { 1, 1, 1,
              1, 1, 1,
              1, 1, 1  
            };                                 

//----------------------------------------------------------------------------------------
const bool * standardNines[10] = { (const bool *)standardNines0, 
                                   (const bool *)standardNines1, 
                                   (const bool *)standardNines2, 
                                   (const bool *)standardNines3, 
                                   (const bool *)standardNines4, 
                                   (const bool *)standardNines5, 
                                   (const bool *)standardNines6,
                                   (const bool *)standardNines7,
                                   (const bool *)standardNines8,
                                   (const bool *)standardNines9 
                                 };
                                   
const uint8_t standardNinesNbPieces[10] = { standardNinesNbPieces0,
                                            standardNinesNbPieces1,
                                            standardNinesNbPieces2,
                                            standardNinesNbPieces3,
                                            standardNinesNbPieces4,
                                            standardNinesNbPieces5,
                                            standardNinesNbPieces6,
                                            standardNinesNbPieces7,
                                            standardNinesNbPieces8,
                                            standardNinesNbPieces9,
                                          };

//----------------------------------------------------------------------------------------
// Color related constants
//----------------------------------------------------------------------------------------

const uint8_t standardColorDifference = 4;

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
    do { standardColorHourRight   = random(33); } while (abs(standardColorHourLeft - standardColorHourRight) < standardColorDifference);
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
void standardGenericDisplay(uint8_t ledStartNumber, uint8_t value, uint8_t pieceNumber, const bool ** pieces, uint8_t piecesSize, uint8_t h, uint8_t s, uint8_t l)
{
  for (uint8_t ledOffset=0; ledOffset < piecesSize; ledOffset++)
  {
    const bool *led_active = pieces[value] + piecesSize*pieceNumber + ledOffset;
    
    if (*led_active)
      ledsSetColor(ledStartNumber + ledOffset, h, s, l);
    else
      ledsSetColor(ledStartNumber + ledOffset, 0, 0, 0);
  }
}
