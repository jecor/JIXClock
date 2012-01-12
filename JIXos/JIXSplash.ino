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
// Startup splash
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// Public API
//----------------------------------------------------------------------------------------

void splashStartup();


//----------------------------------------------------------------------------------------
// Public API Implementation
//----------------------------------------------------------------------------------------

void splashStartup()
{
  Serial.println(F("Splash..."));
  uint8_t h = 0;
  uint8_t l = 64;
  
  for (uint8_t i=0; i<36; i++)
  {
    /*Serial.print("l: ");
    Serial.println((unsigned int)l);*/
    
    ledsBegin();
    
    for (uint8_t led=1; led<=27; led++)
    {
      ledsSetColor(led, h, 255, l);
      
      h += 20;
      if (h > 255)
        h = 0;
    }
    
    ledsEnd();
    
    if (i > 21)
    {
      l -= 4;
      delay(20);
    }
    else
    {
      delay(50);
    } 
  }
}
