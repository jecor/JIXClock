//----------------------------------------------------------------------------------------
// JIXos: JIX Clock operating system
// Copyright (c) 2010-2013 Jérôme Cornet <jerome@aldorande.net>
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
// Real Time Clock Management
//----------------------------------------------------------------------------------------
#ifndef JIX_RTC_H
#define JIX_RTC_H

#include <Arduino.h>

//----------------------------------------------------------------------------------------
// Public API
//----------------------------------------------------------------------------------------

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

// Check the validity of the time passed as arguments, return true if valid
bool rtcCheckTime(uint8_t hour, uint8_t minute, uint8_t second);

// Get user data stored in RTC Memory ; index is between 0 and 30
uint8_t rtcGetMemory(uint8_t index);

// Store user data in RTC Memory ; index is between 0 and 30
void rtcSetMemory(uint8_t index, uint8_t data);

//----------------------------------------------------------------------------------------
// Utilities
//----------------------------------------------------------------------------------------

void rtcDebugBCD(uint8_t value);
void rtcDebugTime();
void rtcDebugTime(uint8_t hour, uint8_t minute, uint8_t second);

#endif
