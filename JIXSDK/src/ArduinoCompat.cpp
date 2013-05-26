/*
 * JIXClock SDK
 * Copyright (c) 2012 Jérôme Cornet
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

#include <iostream>
#include "ArduinoCompat.h"
#include "SDL.h"

// Random function
unsigned int random(unsigned int max)
{
   return rand() % max;
}

void pinMode(unsigned int, unsigned int)
{
}

uint8_t pgm_read_byte_near(const uint8_t *pointer) 
{ 
   return *pointer; 
}

uint16_t pgm_read_word_near(const uint16_t *pointer) 
{ 
   return *pointer; 
}

const char * F(const char * in_string)
{ 
   return in_string; 
}

// Serial class implementation

void serial_class::print(const char *string) 
{ 
   std::cout << string; 
}

void serial_class::println(const char *string) 
{ 
   std::cout << string << std::endl; 
}

void serial_class::print(unsigned int value)
{ 
   std::cout << value; 
}

void serial_class::println(unsigned int value)
{ 
   std::cout << value << std::endl; 
}

void serial_class::begin(unsigned int)
{
}

// Serial class singleton instanciation
serial_class Serial;

// SDL-based implementations
unsigned int millis()
{
   return SDL_GetTicks();
}


