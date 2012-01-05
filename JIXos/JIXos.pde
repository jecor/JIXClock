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
// Main
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
// Constants
//----------------------------------------------------------------------------------------

const unsigned int globalVersionMajor = 1;
const unsigned int globalVersionMinor = 0;

const unsigned int globalNbModes = 13;

unsigned int (*globalModeFunctions[globalNbModes]) (uint8_t hourLeft, 
                                                    uint8_t hourRight, 
                                                    uint8_t minuteLeft, 
                                                    uint8_t minuteRight, 
                                                    uint8_t secondLeft, 
                                                    uint8_t secondRight, 
                                                    uint8_t luminosity,
                                                    bool    hold) =
{
  &standardModeFast,
  &standardModeMedium,
  &standardModeSlow,
  &colorfulModeFast,
  &colorfulModeMedium,
  &colorfulModeSlow,
  &rainbowModeFast,
  &rainbowModeMedium,
  &rainbowModeSlow,
  &secondsMode,
  &secondsBlinkMode,
  &torchMode,
  &colorTestMode,
};

const unsigned int SETH_PIN = 4;
const unsigned int SETM_PIN = 12;

const uint8_t LUMINOSITY_ADDRESS = 0;
const uint8_t MODE_ADDRESS       = 1;

//----------------------------------------------------------------------------------------
// Main globals
//----------------------------------------------------------------------------------------

unsigned int globalMode = 0;
uint8_t      globalLuminosity = 64;
 
unsigned int globalSetHState = 0;
unsigned int globalSetMState = 0;

uint8_t globalHour, globalOldHour = 0;
uint8_t globalMinute, globalOldMinute = 0;
uint8_t globalSecond, globalOldSecond = 0;

uint8_t       globalSetupMode = 0;
bool          globalSetupToggle = false;
bool          globalFirstTime = true;
unsigned long globalLastTime = 0;
double        globalCorrection = 1.0;
bool          globalCorrectionOverride = false;

// Kernel

const unsigned int globalNbTasks = 3;

unsigned int (*globalTasks[globalNbTasks]) (void) =
{
  &manageSetButtonsTask,
  &readRTCTask,
  &updateLEDSTasks
};

const unsigned int manageSetButtonsTaskID = 0;
const unsigned int readRTCTaskID          = 1;
const unsigned int updateLEDSTaskID       = 2;

unsigned int globalTaskRemaining[globalNbTasks] = { 0, 0, 0 };

//----------------------------------------------------------------------------------------
// Implementation
//----------------------------------------------------------------------------------------

void setup()
{
  rtcInit();
  
  ledsInit();
  
  pinMode(SETH_PIN, INPUT);
  pinMode(SETM_PIN, INPUT);
  
  Serial.begin(115200);
  
  restoreSettings();
}

void restoreSettings()
{
  globalLuminosity = rtcGetMemory(LUMINOSITY_ADDRESS);
  
  if ((globalLuminosity < 16)  ||
      (globalLuminosity > 128) ||
      ((globalLuminosity % 16) != 0))
  {
    Serial.println("Invalid luminosity, resetting to 64");
    globalLuminosity = 64;
  }
  
  globalMode = rtcGetMemory(MODE_ADDRESS);
  
  if (globalMode >= globalNbModes)
    globalMode = 0;
}

unsigned int manageSetButtonsTask()
{
  //Serial.println("##manageSetButtonsTask");
  bool setHPressed = (digitalRead(SETH_PIN) == 0);
  bool setMPressed = (digitalRead(SETM_PIN) == 0);
  
  /*Serial.print("SetH: ");
  Serial.print(setHPressed);
  Serial.print(" SetM: ");
  Serial.println(setMPressed);*/
  
  if (setHPressed)
  {
    if (globalSetHState < 10)
      globalSetHState++;
    
    if (globalSetHState > 4)
    {
      if ((globalModeFunctions[globalMode] == &colorTestMode) ||
          (globalModeFunctions[globalMode] == &torchMode))
      {
        // Forbid clock setting in special colorTestMode
        globalSetHState = 0;
      }
      else if (!globalSetupMode)
      {
        globalSetupMode = 1;
        
        delayTask(updateLEDSTaskID, 0); // means immediate execution
        
        rtcHalt();
      }
    }
  }
  else
  {
    if ((globalSetHState >= 1) && (globalSetHState <= 4))
    {
      if (globalSetupMode)
      {
        if (globalSetupMode == 4)
        {
          globalSetupMode = 0;
          globalSetHState = 0;
          rtcStart();
        }
        else
        {
          globalSetupMode++;
          globalSetHState = 0;
        }
      }
      else
      {
        if ((globalSetMState >= 1) && (globalSetMState <= 4))
        {
          setMPressed = 0;
          globalSetMState = 0;
          
          standardMode(0, globalVersionMajor, 0, globalVersionMinor, 0, 0, globalLuminosity, false);
          
          delayTask(updateLEDSTaskID, 2000);
            
          globalCorrectionOverride = true;
        }
        else
        {
          globalMode++;
          if (globalMode >= globalNbModes)
            globalMode = 0;
            
          rtcSetMemory(MODE_ADDRESS, globalMode);
          
          modeDisplay(globalMode);
          
          delayTask(updateLEDSTaskID, 500); 
            
          globalCorrectionOverride = true;
            
          Serial.print("New mode: ");
          Serial.println(globalMode);
        }
      }
    }
    
    globalSetHState = 0;
  }
  
  if (setMPressed)
  {
    globalSetMState++;
  }
  else
  {
    if ((globalSetMState >= 1) && (globalSetMState <= 4))
    {
      if (globalSetupMode)
      {
        switch (globalSetupMode)
        {
          case 1:
            if ((((globalHour >> 4) & 0xF) == 1) && ((globalHour & 0xF) > 3))
            {
              globalHour = 0x20;
            }
            else
            {
              globalHour += 0x10;
              if (globalHour > 0x23)
               globalHour &= 0x0F;
            }
            break;
            
          case 2:
            if ((globalHour & 0xF) < 9)
              globalHour += 0x01;
            else
              globalHour &= 0xF0;
            
            if (globalHour > 0x23)
              globalHour &= 0xF0;
            break;
            
          case 3:
            globalMinute += 0x10;
            if (globalMinute > 0x59)
              globalMinute &= 0x0F;
            break;
            
          case 4:
            if ((globalMinute & 0xF) < 9)
              globalMinute += 0x01;
            else
              globalMinute &= 0xF0;
            break;
            
          default:
            ;
        }
        rtcSetTime(globalHour, globalMinute, 0x80); // Maintain clock in stop mode
      }
      else
      {
        if (globalLuminosity >= 128)
          globalLuminosity = 16;
        else
          globalLuminosity += 16;
          
        Serial.print("New luminosity: ");
        Serial.println(globalLuminosity);
        
        rtcSetMemory(LUMINOSITY_ADDRESS, globalLuminosity);
        
        (*globalModeFunctions[globalMode])((globalHour >> 4) & 0xF, 
                                            globalHour & 0xF, 
                                            (globalMinute >> 4) & 0xF, 
                                            globalMinute & 0xF, 
                                            (globalSecond >> 4) & 0xF, 
                                            globalSecond & 0xF, 
                                            globalLuminosity,
                                            true);
        
        delayTask(updateLEDSTaskID, 500);
      }
    }
    globalSetMState = 0;
  }
  
  return 100;
}

unsigned int readRTCTask()
{
  //Serial.println("##readRTCTask");
  
  rtcGetTime(globalHour, globalMinute, globalSecond);
    
  if (!globalSetupMode && !rtcCheckTime(globalHour, globalMinute, globalSecond))
  {
    Serial.println("Initializing time...");
  
    rtcSetDate(7, 0x01, 0x01, 0x11);
    rtcSetTime(0x13, 0x37, 0x80);
    
    globalSetupMode = 1;
  }
  else if (!globalSetupMode && ((globalHour != globalOldHour) || (globalMinute != globalOldMinute) || (globalSecond != globalOldSecond)))
  {
    globalOldHour = globalHour;
    globalOldMinute = globalMinute;
    globalOldSecond = globalSecond;
    
    if (globalCorrectionOverride)
    {
      globalLastTime = millis();
      globalCorrection = 1.0;
    }
    else
    {
      if (globalFirstTime)
      {
        globalFirstTime = false;
        globalLastTime = millis();
      }
      else
      {
        unsigned long currentTime = millis();
        unsigned long timerDelay = 0;
        if (currentTime >= globalLastTime)
          timerDelay = currentTime - globalLastTime;
        else
          timerDelay = (((unsigned long)-1)-globalLastTime)+currentTime;
          
        /*Serial.print("CurrentTime: ");
        Serial.print(currentTime);
        Serial.print(" LastTime: ");
        Serial.println(globalLastTime);*/
          
        /*Serial.print("timerDelay: ");
        Serial.println(timerDelay);*/
        
        globalCorrection = 1000.0/timerDelay;
        // self resilience: if result is out-of-reasonable bounds, we cancel correction
        if (globalCorrection > 2.0)
          globalCorrection = 1.0;
        
        globalLastTime = currentTime;
      }
    }
    
    rtcDebugTime(globalHour, globalMinute, globalSecond);
  }
  else if (globalCorrectionOverride || globalSetupMode)
  {
    globalLastTime = millis();
    globalCorrection = 1.0;
  }
    
  return 500;
}

unsigned int updateLEDSTasks()
{
  //Serial.println("##updateLEDSTask");
  if (globalCorrectionOverride)
    globalCorrectionOverride = false;
  
  if (globalSetupMode)
  {
    if (globalSetupToggle)
    {
      // Black
      switch (globalSetupMode)
      {
        case 1:
          (*globalModeFunctions[globalMode])(0, 
                                             globalHour & 0xF, 
                                            (globalMinute >> 4) & 0xF, 
                                             globalMinute & 0xF, 
                                             0, 
                                             0, 
                                             globalLuminosity,
                                             true);
         break;
         
         case 2:
          (*globalModeFunctions[globalMode])((globalHour >> 4) & 0xF, 
                                              0, 
                                             (globalMinute >> 4) & 0xF, 
                                              globalMinute & 0xF, 
                                              0, 
                                              0, 
                                              globalLuminosity,
                                              true);
         break;
         
         case 3:
          (*globalModeFunctions[globalMode])((globalHour >> 4) & 0xF, 
                                              globalHour & 0xF, 
                                              0, 
                                              globalMinute & 0xF, 
                                              0, 
                                              0, 
                                              globalLuminosity,
                                              true);
         break;
         
         case 4:
          (*globalModeFunctions[globalMode])((globalHour >> 4) & 0xF, 
                                              globalHour & 0xF, 
                                             (globalMinute >> 4) & 0xF, 
                                              0, 
                                              0, 
                                              0, 
                                              globalLuminosity,
                                              true);
         break;
         
         default:
           ;
      }
    }
    else
    {
      (*globalModeFunctions[globalMode])((globalHour >> 4) & 0xF, 
                                          globalHour & 0xF, 
                                         (globalMinute >> 4) & 0xF, 
                                          globalMinute & 0xF, 
                                          0, 
                                          0, 
                                          globalLuminosity,
                                          true);
    }
    
    globalSetupToggle = !globalSetupToggle;
    
    return 500;
  }
  else
  {
    return (*globalModeFunctions[globalMode])((globalHour >> 4) & 0xF, 
                                              globalHour & 0xF, 
                                              (globalMinute >> 4) & 0xF, 
                                              globalMinute & 0xF, 
                                              (globalSecond >> 4) & 0xF, 
                                              globalSecond & 0xF, 
                                              globalLuminosity,
                                              false);
  }
}

// A value of zero means: immediate execution of the task
void delayTask(unsigned int taskID, unsigned int value)
{
  if (globalTaskRemaining[taskID] < value)
    globalTaskRemaining[taskID] += value;
  else
    globalTaskRemaining[taskID] = value;
}

void kernel()
{
  while (true)
  {
    for (unsigned int i=0; i<globalNbTasks; i++)
    {
      if (globalTaskRemaining[i] == 0)
      {
        globalTaskRemaining[i] = (*globalTasks[i])();
      }
    }
    
    unsigned int minWait = globalTaskRemaining[0];
    for (unsigned int i=1; i<globalNbTasks; i++)
    {
     if (globalTaskRemaining[i] < minWait)
     {
       minWait = globalTaskRemaining[i];
     }
    }
    
    /*Serial.print("minWait: ");
    Serial.println(minWait);*/
    
    delay(minWait*globalCorrection);
    for (unsigned int i=0; i<globalNbTasks; i++)
    {
       if (globalTaskRemaining[i] >= minWait)
         globalTaskRemaining[i] -= minWait;
       else
         globalTaskRemaining[i] = 0;
    }
  }
}

void loop()
{
  Serial.print("JIXos version ");
  Serial.print(globalVersionMajor);
  Serial.print(".");
  Serial.println(globalVersionMinor);
  
  splashStartup();
  
  kernel();
}

