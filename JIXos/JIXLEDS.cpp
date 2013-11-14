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
// RGB LEDs Management
//----------------------------------------------------------------------------------------
#include <Tlc5940.h>
#include "JIXLEDS.h"

//----------------------------------------------------------------------------------------
// Private functions
//----------------------------------------------------------------------------------------

// Convert a 8-bit HSL value into a 12-bit RGB value
void ledsHSLToRGB(uint8_t inh, uint8_t ins, uint8_t inl, uint16_t & outr, uint16_t & outg, uint16_t & outb);

//----------------------------------------------------------------------------------------
// Constants
//----------------------------------------------------------------------------------------
const unsigned int LAST_LED_PIN   = 5;

const uint8_t ledsRedCorrection[27]   = { 100, 95, 98, 97, 98, 94, 100, 94, 100, 89, 91, 95, 88, 89, 95, 92, 89, 89, 92, 92, 89, 89, 89, 88, 46, 94, 88};
const uint8_t ledsGreenCorrection[27] = { 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};
const uint8_t ledsBlueCorrection[27]  = { 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};

//----------------------------------------------------------------------------------------
// Public API Implementation
//----------------------------------------------------------------------------------------

void ledsInit()
{ 
  pinMode(LAST_LED_PIN, OUTPUT);
  digitalWrite(LAST_LED_PIN, 1);
  
  Tlc.init();
}

// Call before updating the LEDs
void ledsBegin()
{
  Tlc.clear();
}

// Call after updating the LEDs
void ledsEnd()
{
  Tlc.update();
}

// Set the HSL color of the LED #ledNumber
void ledsSetColor(uint8_t ledNumber, uint8_t h, uint8_t s, uint8_t l)
{
  uint16_t r, g, b;
    
  ledsHSLToRGB(h, s, l, r, g, b);
  
  r = r * (ledsRedCorrection[ledNumber - 1] / 100.0);
  g = g * (ledsGreenCorrection[ledNumber - 1] / 100.0);
  b = b * (ledsBlueCorrection[ledNumber - 1] / 100.0);
  
  // Special cases
  
  // D27: blue LED is driven by Arduino directly
  if (ledNumber == 27)
  {
    Tlc.set(3*(ledNumber-1) + 0, r);
    Tlc.set(3*(ledNumber-1) + 1, g);
    analogWrite(LAST_LED_PIN, 255 - (b >> 4));
  }
  else if (ledNumber == 22) // D22: remap to D23 (hardware bug)
  {
    Tlc.set(3*22 + 0, r);
    Tlc.set(3*22 + 1, g);
    Tlc.set(3*22 + 2, b);
    analogWrite(LAST_LED_PIN, 255);
  }
  else if (ledNumber == 23) // D23: remap to D22 (hardware bug)
  {
    Tlc.set(3*21 + 0, r);
    Tlc.set(3*21 + 1, g);
    Tlc.set(3*21 + 2, b);
    analogWrite(LAST_LED_PIN, 255);
  } 
  else // Normal case
  {  
    Tlc.set(3*(ledNumber-1) + 0, r);
    Tlc.set(3*(ledNumber-1) + 1, g);
    Tlc.set(3*(ledNumber-1) + 2, b);
    analogWrite(LAST_LED_PIN, 255);
  }
}

// Set the RGB color of the LED #ledNumber
void ledsSetRGBColor(uint8_t ledNumber, uint8_t r, uint8_t g, uint8_t b)
{
  unsigned long mr, mg, mb;
  
  mr = r << 4;
  mg = g << 4;
  mb = b << 4;
  
  // Special cases
  
  // D27: blue LED is driven by Arduino directly
  if (ledNumber == 27)
  {
    Tlc.set(3*(ledNumber-1) + 0, mr);
    Tlc.set(3*(ledNumber-1) + 1, mg);
    analogWrite(LAST_LED_PIN, 255 - (mb >> 4));
    
    Serial.print("last_led: ");
    Serial.println(255 - (mb >> 4));
  }
  else if (ledNumber == 22) // D22: remap to D23 (hardware bug)
  {
    Tlc.set(3*22 + 0, mr);
    Tlc.set(3*22 + 1, mg);
    Tlc.set(3*22 + 2, mb);
    analogWrite(LAST_LED_PIN, 255);
  }
  else if (ledNumber == 23) // D23: remap to D22 (hardware bug)
  {
    Tlc.set(3*21 + 0, mr);
    Tlc.set(3*21 + 1, mg);
    Tlc.set(3*21 + 2, mb);
    analogWrite(LAST_LED_PIN, 255);
  } 
  else // Normal case
  {  
    Tlc.set(3*(ledNumber-1) + 0, mr);
    Tlc.set(3*(ledNumber-1) + 1, mg);
    Tlc.set(3*(ledNumber-1) + 2, mb);
    analogWrite(LAST_LED_PIN, 255);
  }
}

//----------------------------------------------------------------------------------------
// Low-Level Implementation
//----------------------------------------------------------------------------------------

// Convert a 8-bit HSL value into a 12-bit RGB value
void ledsHSLToRGB(uint8_t inh, uint8_t ins, uint8_t inl, uint16_t & outr, uint16_t & outg, uint16_t & outb)
{
  double h, sl, l;
  
  h = inh/256.0; // allow inh = 255
  sl = ins/255.0;
  l = inl/255.0;
  
  double v;
  double r,g,b;
 
  r = l;   // default to gray
  g = l;
  b = l;
  v = (l <= 0.5) ? (l * (1.0 + sl)) : (l + sl - l * sl);
  if (v > 0)
  {
    double m;
    double sv;
    int sextant;
    double fract, vsf, mid1, mid2;
 
    m = l + l - v;
    sv = (v - m ) / v;
    h *= 6.0;
    sextant = (int)h;
    fract = h - sextant;
    vsf = v * sv * fract;
    mid1 = m + vsf;
    mid2 = v - vsf;
    switch (sextant)
    {
      case 0:
        r = v;
        g = mid1;
        b = m;
        break;
      case 1:
        r = mid2;
        g = v;
        b = m;
        break;
      case 2:
        r = m;
        g = v;
        b = mid1;
        break;
      case 3:
        r = m;
        g = mid2;
        b = v;
        break;
      case 4:
        r = mid1;
        g = m;
        b = v;
        break;
      case 5:
        r = v;
        g = m;
        b = mid2;
        break;
     }
   }
   
   outr = r*4095;
   outg = g*4095;
   outb = b*4095;
}

