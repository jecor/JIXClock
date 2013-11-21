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
#include "SDL.h"
#include "JIXhal.h"
#include "JIXrtc.h"
#include "JIXconstants.h"

SDL_Event user_event;

Uint32 timer_callback(Uint32 interval, void *)
{
   user_event.type=SDL_USEREVENT;
   user_event.user.code=2;
   user_event.user.data1=NULL;
   user_event.user.data2=NULL;
   SDL_PushEvent(&user_event);
   
   return interval;
}

void delay(unsigned int value)
{
   SDL_TimerID timer = SDL_AddTimer(value, &timer_callback, 0);
   
   SDL_Event    event;
   
   while (SDL_WaitEvent(&event))
   {
      switch (event.type)
      {
         //case SDL_KEYDOWN:
         case SDL_QUIT:
            rtcSaveMemory(memoryFileName);
            SDL_Quit();
            exit(0);
            break;
            
         case SDL_VIDEOEXPOSE:
            // refresh
            //drawBackground(main_screen);
            break;
            
         case SDL_VIDEORESIZE:
            break;
            
         case SDL_USEREVENT:
            //std::cout << "removed timer" << std::endl;
            SDL_RemoveTimer(timer);
            return;
            break;
            
         default:
            ;
      }
   }
   
   std::cout << "Should not be there..." << std::endl;
}

int get_free_memory()
{
   return 2048;
}
