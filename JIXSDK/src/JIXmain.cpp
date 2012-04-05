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
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <inttypes.h>
#include <sstream>

#include "SDL.h"
#include "ArduinoCompat.h"
#include "JIXhal.h"
#include "JIXgraphics.h"
#include "JIXrtc.h"

extern SDL_Surface  *main_screen;

void setup();
void loop();

int main(int argc, char *argv[])
{
   unsigned int width, height, bpp;
   
   width = 640;
   
   for (int i=1; i<argc; i++)
   {
      std::string currentArg(argv[i]);
   
      if ((currentArg == std::string("-h")) ||
          (currentArg == std::string("--help")))
      {
         std::cout << "usage: " << argv[0] << " [ -options ... ]" << std::endl;
         std::cout << "where options include:" << std::endl << std::endl;
         std::cout << "   -h, --help          display this help message" << std::endl;
         std::cout << "   -w, --width value   set the width of the window (corresponding height is determined automatically)" << std::endl;
         std::cout << std::endl;
         
         return 0;
      }
      else if ((currentArg == std::string("-w")) ||
               (currentArg == std::string("--width")))
      {
         if ((i+1) < argc)
         {
            std::stringstream ss(argv[i+1]);

            ss >> width;            
         }
         else
         {
            std::cerr << "You must provide a value with " << currentArg << " option!" << std::endl;
            return 1;
         }
      }
   }
   
   Uint32       videoFlags;
         
   if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
   {
      fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
      exit(1);
   }
   
   height = width / CLOCK_ASPECT_RATIO;
   bpp    = 32;
   videoFlags = SDL_SWSURFACE;

   main_screen = SDL_SetVideoMode(width, height, bpp, videoFlags);
   if (main_screen == NULL)
   {
      fprintf(stderr, "Failed to set video mode: %s\n", SDL_GetError());
      exit(2);
   }
   
   SDL_WM_SetCaption("JIXsimulator", "");
   
   rtcLoadMemory(memoryFileName);
   
   drawBackground(main_screen);
   drawLEDs(main_screen);
   
   setup();
   loop();
   
   return 0;
}

