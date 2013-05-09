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
// Demo mode cycling between "interesting" modes
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// Public API
//----------------------------------------------------------------------------------------

unsigned int demoMode(uint8_t hourLeft, 
                      uint8_t hourRight, 
                      uint8_t minuteLeft, 
                      uint8_t minuteRight, 
                      uint8_t secondLeft, 
                      uint8_t secondRight, 
                      uint8_t luminosity,
                      bool    hold);

                           
//----------------------------------------------------------------------------------------
// Externs
//----------------------------------------------------------------------------------------

// NOTHING FOR NOW

//----------------------------------------------------------------------------------------
// Variables (to store current state of pieces for hold mode)
//----------------------------------------------------------------------------------------
uint8_t      demoCurrentMode = 0;
unsigned int demoTotalTime = 0;

//----------------------------------------------------------------------------------------
// Public API Implementation
//----------------------------------------------------------------------------------------

unsigned int demoMode(uint8_t hourLeft, 
                      uint8_t hourRight, 
                      uint8_t minuteLeft, 
                      uint8_t minuteRight, 
                      uint8_t secondLeft, 
                      uint8_t secondRight, 
                      uint8_t luminosity,
                      bool    hold)
{  
  unsigned int taskDelay = (*globalModeFunctions[demoCurrentMode])(hourLeft, hourRight, minuteLeft, minuteRight, secondLeft, secondRight, luminosity, hold);
  
  if (!hold)
  {
    demoTotalTime += taskDelay;
    
    /*Serial.print("demoTotalTime: ");
    Serial.println(demoTotalTime);*/
    
    if (demoTotalTime >= 60000)
    {
      demoTotalTime = 0;
      demoCurrentMode = random(9);
        
      Serial.print("Demo new mode: ");
      Serial.println(demoCurrentMode);
    }
  }
  
  return taskDelay;
}

