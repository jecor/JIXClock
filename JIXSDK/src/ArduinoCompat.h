/*
 * JIXClock SDK
 * Copyright (c) 2012-2013 Jérôme Cornet
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <inttypes.h>
#include <math.h>
#include <iostream>
#include <time.h>

//-----------------------------------------------------------------
// Preprocessor-based implementation
//-----------------------------------------------------------------

#define PROGMEM

#define INPUT  0
#define OUTPUT 1

//-----------------------------------------------------------------
// Types
//-----------------------------------------------------------------
typedef uint8_t prog_uint8_t;
typedef uint16_t prog_uint16_t;

//-----------------------------------------------------------------
// Arduino functions
//-----------------------------------------------------------------
unsigned int abs(unsigned int value);

unsigned int random(unsigned int max);

uint8_t pgm_read_byte_near(const uint8_t *pointer);

uint16_t pgm_read_word_near(const uint16_t *pointer);

void pinMode(unsigned int, unsigned int);

unsigned int millis();

const char * F(const char * in_string);

void delay(unsigned int value);

//-----------------------------------------------------------------
// Serial class
//-----------------------------------------------------------------

class serial_class
{
public:
    
   void print(const char *string);
   void println(const char *string);
    
   void print(unsigned int value);
   void println(unsigned int value);
    
   void begin(unsigned int);
};

extern serial_class Serial;





