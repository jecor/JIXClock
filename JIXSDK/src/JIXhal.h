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

#include <inttypes.h>
#include <stdlib.h>

//-----------------------------------------------------------------
// LEDs functions
//-----------------------------------------------------------------

void ledsBegin();
void ledsEnd();

void ledsHSLToRGB(uint8_t inh, uint8_t ins, uint8_t inl, uint16_t & outr, uint16_t & outg, uint16_t & outb);

void ledsSetColor(uint8_t ledNumber, uint8_t h, uint8_t s, uint8_t l);

void ledsSetRGBColor(uint8_t ledNumber, uint8_t r, uint8_t g, uint8_t b);

//-----------------------------------------------------------------
// Real Time Clock functions
//-----------------------------------------------------------------

// Initialize the RTC
void rtcInit();

// Set the time of RTC
void rtcSetTime(uint8_t hour, uint8_t minute, uint8_t second);

// Set the date of RTC
void rtcSetDate(uint8_t day, uint8_t date, uint8_t month, uint8_t year);

// Start the RTC
void rtcStart();

// Halt the RTC
void rtcHalt();

// Get the time of RTC
void rtcGetTime(uint8_t & hour, uint8_t & minute, uint8_t & second);

bool rtcCheckTime(uint8_t hour, uint8_t minute, uint8_t second);

void ledsInit();

uint8_t rtcGetMemory(unsigned int address);

void rtcSetMemory(unsigned int address, uint8_t data);

void rtcDebugBCD(uint8_t value);

void rtcDebugTime(uint8_t hour, uint8_t minute, uint8_t second);

//-----------------------------------------------------------------
// Utilities
//-----------------------------------------------------------------
int get_free_memory();

//-----------------------------------------------------------------
// Buttons
//-----------------------------------------------------------------
void buttonsInit();

bool buttonsGetModeState();

bool buttonsGetIncrementState();

