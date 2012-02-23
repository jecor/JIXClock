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
#include <math.h>
#include <iostream>
#include <time.h>

void ledsBegin();
void ledsEnd();

void ledsHSLToRGB(uint8_t inh, uint8_t ins, uint8_t inl, uint16_t & outr, uint16_t & outg, uint16_t & outb);

void ledsSetColor(uint8_t ledNumber, uint8_t h, uint8_t s, uint8_t l);

void ledsSetRGBColor(uint8_t ledNumber, uint8_t r, uint8_t g, uint8_t b);

inline uint8_t pgm_read_byte_near(const uint8_t *pointer) { return *pointer; }

unsigned int abs(unsigned int value);

inline unsigned int random(unsigned int max)
{
    return rand() % max;
}

typedef uint8_t prog_uint8_t ;

inline const char * F(const char * in_string) { return in_string; }

class serial_class
{
public:
    
    void print(const char *string) { std::cout << string; }
    void println(const char *string) { std::cout << string << std::endl; }
    
    void print(unsigned int value) { std::cout << value; }
    void println(unsigned int value) { std::cout << value << std::endl; }
    
    void begin(unsigned int) {}
};

extern serial_class Serial;

void delay(unsigned int value);

#define PROGMEM

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
inline void rtcGetTime(uint8_t & hour, uint8_t & minute, uint8_t & second)
{
   time_t rawtime;
   struct tm * timeinfo;
   
   time(&rawtime);
   timeinfo = localtime(&rawtime);
   
   hour = ((timeinfo->tm_hour / 10) << 4) + ((timeinfo->tm_hour) % 10);
   minute = ((timeinfo->tm_min / 10) << 4) + ((timeinfo->tm_min) % 10);
   second = ((timeinfo->tm_sec / 10) << 4) + ((timeinfo->tm_sec) % 10);
   
   /*hour = 0x13;
   minute = 0x50;
   second = 0x00;*/
}

inline bool rtcCheckTime(uint8_t hour, uint8_t minute, uint8_t second)
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

inline void ledsInit() {}

#define INPUT 0
#define OUTPUT 1

inline void pinMode(unsigned int, unsigned int) {}

inline uint8_t rtcGetMemory(unsigned int address) { return 0; }
inline unsigned int digitalRead(unsigned int pinNumber) { return 1; }

inline void rtcSetMemory(unsigned int address, uint8_t data) {}

inline void rtcDebugBCD(uint8_t value)
{
    Serial.print((value & 0xF0) >> 4);
    Serial.print(value & 0xF);
}

inline void rtcDebugTime(uint8_t hour, uint8_t minute, uint8_t second)
{
    rtcDebugBCD(hour);
    Serial.print(":");
    rtcDebugBCD(minute);
    Serial.print(":");
    rtcDebugBCD(second);
    Serial.println("");
}

inline int get_free_memory() { return 2048; }

unsigned int millis();

