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
// Standard Mode with Tetris-like display - constants
//----------------------------------------------------------------------------------------
#ifndef JIX_STANDARD_CONSTANTS_H
#define JIX_STANDARD_CONSTANTS_H

#include <Arduino.h>

//----------------------------------------------------------------------------------------
// Constants for 3 LEDs displays
//----------------------------------------------------------------------------------------

const unsigned int standardThreesSize  = 3;

//----------------------------------------------------------------------------------------
const uint8_t standardThreesNbPieces0 = 1;

const prog_uint8_t standardThrees0[standardThreesNbPieces0 * standardThreesSize] PROGMEM = 
            { 0,
              0,
              0,  
            };

//----------------------------------------------------------------------------------------
const uint8_t standardThreesNbPieces1 = 3;

const prog_uint8_t standardThrees1[standardThreesNbPieces1 * standardThreesSize] PROGMEM = 
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

const prog_uint8_t standardThrees2[standardThreesNbPieces2 * standardThreesSize] PROGMEM = 
            { 1,
              1,
              0,
            
              0,
              1,
              1  
            };

//----------------------------------------------------------------------------------------
static const uint8_t * standardThrees[3] = { (const uint8_t *)standardThrees0, 
                                             (const uint8_t *)standardThrees1, 
                                             (const uint8_t *)standardThrees2
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

const prog_uint8_t standardSix0[standardSixNbPieces0 * standardSixSize] PROGMEM = 
            { 0, 0,
              0, 0,
              0, 0 
            };

//----------------------------------------------------------------------------------------
const uint8_t standardSixNbPieces1 = 6;

const prog_uint8_t standardSix1[standardSixNbPieces1 * standardSixSize] PROGMEM = 
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

const prog_uint8_t standardSix2[standardSixNbPieces2 * standardSixSize] PROGMEM = 
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

const prog_uint8_t standardSix3[standardSixNbPieces3 * standardSixSize] PROGMEM = 
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

const prog_uint8_t standardSix4[standardSixNbPieces4 * standardSixSize] PROGMEM = 
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

const prog_uint8_t standardSix5[standardSixNbPieces5 * standardSixSize] PROGMEM = 
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
static const uint8_t * standardSix[6] = { (const uint8_t *)standardSix0, 
                                          (const uint8_t *)standardSix1, 
                                          (const uint8_t *)standardSix2,
                                          (const uint8_t *)standardSix3,
                                          (const uint8_t *)standardSix4,
                                          (const uint8_t *)standardSix5
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

const prog_uint8_t standardNines0[standardNinesNbPieces0 * standardNinesSize] PROGMEM = 
            { 0, 0, 0,
              0, 0, 0,
              0, 0, 0  
            };

//----------------------------------------------------------------------------------------                        
const uint8_t standardNinesNbPieces1 = 9;

const prog_uint8_t standardNines1[standardNinesNbPieces1 * standardNinesSize] PROGMEM = 
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

const prog_uint8_t standardNines2[standardNinesNbPieces1 * standardNinesSize] PROGMEM = 
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

const prog_uint8_t standardNines3[standardNinesNbPieces3 * standardNinesSize] PROGMEM = 
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

const prog_uint8_t standardNines4[standardNinesNbPieces4 * standardNinesSize] PROGMEM = 
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

const prog_uint8_t standardNines5[standardNinesNbPieces5 * standardNinesSize] PROGMEM = 
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

const prog_uint8_t standardNines6[standardNinesNbPieces6 * standardNinesSize] PROGMEM = 
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

const prog_uint8_t standardNines7[standardNinesNbPieces7 * standardNinesSize] PROGMEM = 
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

const prog_uint8_t standardNines8[standardNinesNbPieces8 * standardNinesSize] PROGMEM = 
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

const prog_uint8_t standardNines9[standardNinesNbPieces9 * standardNinesSize] PROGMEM = 
            { 1, 1, 1,
              1, 1, 1,
              1, 1, 1  
            };                                 

//----------------------------------------------------------------------------------------
static const uint8_t * standardNines[10] = { (const uint8_t *)standardNines0, 
                                             (const uint8_t *)standardNines1, 
                                             (const uint8_t *)standardNines2, 
                                             (const uint8_t *)standardNines3, 
                                             (const uint8_t *)standardNines4, 
                                             (const uint8_t *)standardNines5, 
                                             (const uint8_t *)standardNines6,
                                             (const uint8_t *)standardNines7,
                                             (const uint8_t *)standardNines8,
                                             (const uint8_t *)standardNines9 
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

#endif
