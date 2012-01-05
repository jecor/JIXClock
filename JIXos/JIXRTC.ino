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
// Real Time Clock Management
//----------------------------------------------------------------------------------------

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

//----------------------------------------------------------------------------------------
// Constants
//----------------------------------------------------------------------------------------

const unsigned int RTC_CE_PIN     = 8;
const unsigned int RTC_IO_PIN     = 7;
const unsigned int RTC_SCLK_PIN   = 6;

//----------------------------------------------------------------------------------------
// Public API Implementation
//----------------------------------------------------------------------------------------

// Initialize the RTC
void rtcInit()
{
  pinMode(RTC_CE_PIN, OUTPUT);
  digitalWrite(RTC_CE_PIN, 0);
  
  pinMode(RTC_SCLK_PIN, OUTPUT);
  digitalWrite(SCLK_PIN, 0);
  
  pinMode(RTC_IO_PIN, INPUT);
  digitalWrite(RTC_IO_PIN, 0);
  
  // Enable charging
  rtcWriteByte(0x90, 0xA5);
}

// Set the time of RTC
void rtcSetTime(uint8_t hour, uint8_t minute, uint8_t second)
{
  rtcWriteByte(0x80, second);
  rtcWriteByte(0x82, minute);
  rtcWriteByte(0x84, hour);
}

// Start the RTC
void rtcStart()
{
  rtcWriteByte(0x80, 0); // Bit 7 of seconds to 0 = RTC Started
}

// Halt the RTC
void rtcHalt()
{
  rtcWriteByte(0x80, 0x80); // Bit 7 of seconds to 1 = RTC Halted
}

// Set the date of RTC
void rtcSetDate(uint8_t day, uint8_t date, uint8_t month, uint8_t year)
{
  rtcWriteByte(0x8A, day);
  rtcWriteByte(0x86, date);
  rtcWriteByte(0x88, month);
  rtcWriteByte(0x8C, year);
}

// Get the time of RTC
void rtcGetTime(uint8_t & hour, uint8_t & minute, uint8_t & second)
{
  hour    = rtcReadByte(0x85);
  minute  = rtcReadByte(0x83);
  second  = rtcReadByte(0x81);
}


// Get the date of RTC
void rtcGetDate(uint8_t & day, uint8_t & date, uint8_t & month, uint8_t & year)
{
  day   = rtcReadByte(0x8B);
  date  = rtcReadByte(0x87);
  month = rtcReadByte(0x89);
  year  = rtcReadByte(0x8D);
}

// Get user data stored in RTC Memory ; index is between 0 and 30
uint8_t rtcGetMemory(uint8_t index)
{
  return rtcReadByte(0xC1 + 2*index);
}

// Store user data in RTC Memory ; index is between 0 and 30
void rtcSetMemory(uint8_t index, uint8_t data)
{
  rtcWriteByte(0xC0 + 2*index, data);
}

// Check the validity of the time passed as arguments, return true if valid
bool rtcCheckTime(uint8_t hour, uint8_t minute, uint8_t second)
{
  if ((hour == 0x00) && (minute == 0x00) && (second == 0x80))
    return false;
  else
  {
    if (((hour >> 4) & 0xF) > 2)
      return false;
      
    if ((hour & 0xF) > 9)
      return false;
      
    if (((minute >> 4) & 0xF) > 5)
      return false;
      
    if ((minute & 0xF) > 9)
      return false;
      
    if (((second >> 4) & 0xF) > 5)
      return false;
      
    if ((second & 0xF) > 9)
      return false;
  }
  
  return true;
}

//----------------------------------------------------------------------------------------
// Low-Level Implementation
//----------------------------------------------------------------------------------------

// Macro used to pause between each pin state change
#define JDELAY delayMicroseconds(1);

// Write one byte of data at address
void rtcWriteByte(uint8_t address, uint8_t data)
{
  int i;
  
  pinMode(RTC_IO_PIN, OUTPUT);
  digitalWrite(RTC_IO_PIN, 0);
  
  // begin transfer
  digitalWrite(RTC_CE_PIN, 1);
  
  rtcWriteBit(0); // WRITE
  for (i=1; i<8; i++)
    rtcWriteBit((address >> i) & 1);
  
  for (i=0; i<8; i++)
    rtcWriteBit((data >> i) & 1);
  
  JDELAY;  
  digitalWrite(RTC_CE_PIN, 0);
}

// Read one byte of data at address and return the result
uint8_t rtcReadByte(uint8_t address)
{
  int i;
  uint8_t ret;
  
  pinMode(RTC_IO_PIN, OUTPUT);
  
  // begin transfer
  digitalWrite(RTC_CE_PIN, 1);
  
  rtcWriteBit(1); // READ
  for (i=1; i<7; i++)
    rtcWriteBit((address >> i) & 1);
  
  rtcWriteBitLast((address >> 7) & 1);
  
  digitalWrite(RTC_IO_PIN, 0);
  pinMode(RTC_IO_PIN, INPUT);
  
  ret = 0;
  for (i=0; i<7; i++)
    ret |= (rtcReadBit() & 1) << i;
    
  ret |= (rtcReadBitLast() & 1) << 7;
  
  JDELAY;  
  digitalWrite(RTC_CE_PIN, 0);
  
  return ret;
}

// Write one bit of data on RTC three-wire bus
void rtcWriteBit(unsigned int bit_value)
{
  digitalWrite(RTC_IO_PIN, bit_value);
  JDELAY;
  digitalWrite(RTC_SCLK_PIN, 1);
  JDELAY;
  digitalWrite(RTC_SCLK_PIN, 0);
  JDELAY;
}

// Write the last bit of data on RTC three-wire bus
void rtcWriteBitLast(unsigned int bit_value)
{
  digitalWrite(RTC_IO_PIN, bit_value);
  JDELAY;
  digitalWrite(RTC_SCLK_PIN, 1);
  JDELAY;
}

// Read one bit of data on RTC three-wire bus
unsigned int rtcReadBit()
{
  unsigned int ret = 0;
  
  digitalWrite(RTC_SCLK_PIN, 0);
  JDELAY;
  ret = digitalRead(RTC_IO_PIN);
  JDELAY;
  digitalWrite(RTC_SCLK_PIN, 1);
  JDELAY;
  
  return ret;
}

// Read the last bit of data on RTC three-wire bus
unsigned int rtcReadBitLast()
{
  unsigned int ret = 0;
  
  digitalWrite(RTC_SCLK_PIN, 0);
  JDELAY;
  ret = digitalRead(RTC_IO_PIN);
  JDELAY;
  
  return ret;
}

//----------------------------------------------------------------------------------------
// Utilities implementation
//----------------------------------------------------------------------------------------

void rtcDebugTime()
{
  uint8_t hour, minute, second, day, date, month, year;
  
  unsigned long startTime = millis();
  
  rtcGetDate(day, date, month, year);
  rtcGetTime(hour, minute, second);
  
  unsigned long endTime = millis();
  
  /*Serial.print("time to read: ");
  Serial.println(endTime - startTime);*/
  
  switch (day)
  {
    case 1:
      Serial.print("Lundi");
      break;
      
    case 2:
      Serial.print("Mardi");
      break;
      
    case 3:
      Serial.print("Mercredi");
      break;
      
    case 4:
      Serial.print("Jeudi");
      break;
      
    case 5:
      Serial.print("Vendredi");
      break;
      
    case 6:
      Serial.print("Samedi");
      break;
      
    case 7:
      Serial.print("Dimanche");
      break;
  }
  
  Serial.print(" ");
  
  rtcDebugBCD(date);
  Serial.print("/");
  rtcDebugBCD(month);
  Serial.print("/20");
  rtcDebugBCD(year);
  Serial.print(" ");
  rtcDebugBCD(hour);
  Serial.print(":");
  rtcDebugBCD(minute);
  Serial.print(":");
  rtcDebugBCD(second);
  Serial.println("");
}

void rtcDebugTime(uint8_t hour, uint8_t minute, uint8_t second)
{
  rtcDebugBCD(hour);
  Serial.print(":");
  rtcDebugBCD(minute);
  Serial.print(":");
  rtcDebugBCD(second);
  Serial.println("");
}

void rtcDebugBCD(uint8_t value)
{
  Serial.print((value & 0xF0) >> 4);
  Serial.print(value & 0xF);
}


