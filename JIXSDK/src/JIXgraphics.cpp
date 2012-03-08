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

#include <stdio.h>
#include "SDL.h"
#include "JIXHal.h"
#include "JIXgraphics.h"

//-----------------------------------------------------------------
// Constants and global variables
//-----------------------------------------------------------------

unsigned int  redLed[27];
unsigned int  greenLed[27];
unsigned int  blueLed[27];
SDL_Surface  *main_screen;

const uint8_t modeDisplayScanOrder[27] = 
 { 25, 16, 17, 18, 10, 11, 1, 2, 3,
   26, 19, 20, 21, 12, 13, 4, 5, 6,
   27, 22, 23, 24, 14, 15, 7, 8, 9 };

void drawLEDs(SDL_Surface * screen);

//-----------------------------------------------------------------
// LEDs functions
//-----------------------------------------------------------------
void ledsInit()
{
}

void ledsBegin()
{
}

void ledsEnd()
{
   drawLEDs(main_screen);
}

// Set the HSL color of the LED #ledNumber
void ledsSetColor(uint8_t ledNumber, uint8_t h, uint8_t s, uint8_t l)
{
   uint16_t r, g, b;
   
   if (ledNumber > 27)
   {
      fprintf(stderr, "Illegal LED index %d!\n", ledNumber);
      return;
   }
   
   ledsHSLToRGB(h, s, l*1.3, r, g, b);
   
   /*r = r * (ledsRedCorrection[ledNumber - 1] / 100.0);
    g = g * (ledsGreenCorrection[ledNumber - 1] / 100.0);
    b = b * (ledsBlueCorrection[ledNumber - 1] / 100.0);*/
   
   redLed[ledNumber] = r;
   greenLed[ledNumber] = g;
   blueLed[ledNumber] = b;
}

// Set the RGB color of the LED #ledNumber
void ledsSetRGBColor(uint8_t ledNumber, uint8_t r, uint8_t g, uint8_t b)
{
   unsigned long mr, mg, mb;
   
   mr = r << 4;
   mg = g << 4;
   mb = b << 4;
   
   if (ledNumber > 27)
   {
      fprintf(stderr, "Illegal LED index %d!\n", ledNumber);
      return;
   }
   
   redLed[ledNumber] = mr;
   greenLed[ledNumber] = mg;
   blueLed[ledNumber] = mb;
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
   
   outr = r*255;
   outg = g*255;
   outb = b*255;
}

void drawLEDs(SDL_Surface * screen)
{
   unsigned int x, y, i;
   
   Uint32   color;
   SDL_Rect rect;
   
   rect.h = screen->w / SQUARE_SIZE_RATIO;
   rect.w = rect.h;
   
   rect.y = screen->w / BORDER_SIZE_RATIO;
   
   i = 0;
   for (y = 0; y<3; y++)
   {
      rect.x = screen->w / BORDER_SIZE_RATIO;
      
      for (x = 0; x<9; x++, i++)
      {         
         int index = modeDisplayScanOrder[i];
         
         color = SDL_MapRGB(screen->format, redLed[index], greenLed[index], blueLed[index]);
         
         SDL_FillRect(screen, &rect, color);
         
         rect.x += screen->w / SQUARE_SIZE_RATIO;
         
         switch (x)
         {
            case 0:
            case 3:
            case 5:
               rect.x += screen->w / INTER_SIZE_RATIO;
               break;
               
            case 1:
            case 2:
            case 4:
            case 6:
            case 7:
               rect.x += screen->w / MINI_SIZE_RATIO;
               break;
         }
      }
      
      rect.y += (screen->w / MINI_SIZE_RATIO) + (screen->w / SQUARE_SIZE_RATIO);
   }   
   
   if (screen->flags & SDL_DOUBLEBUF)
   {
      SDL_Flip(screen);
   }
   else
   {
      SDL_UpdateRect(screen, 0, 0, 0, 0);
   }
}

void drawBackground(SDL_Surface *screen)
{
   int      i;
   Uint32   color;
   Uint8    gradient;
   SDL_Rect rect;
   
   rect.w = screen->w;
   rect.h = 1;
   rect.x = 0;
   
   for (i=0; i<screen->h; i++)
   {
      rect.y = i;
      
      if (i < (screen->h/2))
      {
         gradient = 127 + (i*127/((screen->h)/2) - 1);
      }
      else
      {
         gradient = 127 + ((screen->h - i)*127/((screen->h)/2) - 1);
      }
      
      color = SDL_MapRGB(screen->format, gradient, gradient, gradient);
      
      SDL_FillRect(screen, &rect, color);
   }
   
   if (screen->flags & SDL_DOUBLEBUF)
   {
      SDL_Flip(screen);
   }
   else
   {
      SDL_UpdateRect(screen, 0, 0, 0, 0);
   }
}

SDL_Surface * createScreen(Uint16 w, Uint16 h, Uint8 bpp, Uint32 flags)
{
	SDL_Surface *screen;
   
	/* Set the video mode */
	screen = SDL_SetVideoMode(w, h, bpp, flags);
	if (screen == NULL) 
   {
		fprintf(stderr, "Could not set display mode: %s\n", SDL_GetError());
		return NULL;
	}
   
   return screen;
}
