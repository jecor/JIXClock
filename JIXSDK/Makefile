# 
# JIXClock SDK  
# Copyright (c) 2012 JŽr™me Cornet
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

#---------------------------------------------------------------------

ARDUINOFILES = JIXos.ino

ARDUINOCPP   = JIXColorTestMode.cpp    \
               JIXColorfulMode.cpp     \
               JIXModeDisplay.cpp      \
               JIXRainbowMode.cpp      \
               JIXSecondsBlinkMode.cpp \
               JIXSecondsMode.cpp      \
               JIXSplash.cpp           \
               JIXStandardMode.cpp     \
               JIXTorchMode.cpp        \
               JIXDemoMode.cpp

SRCSFILES    = ArduinoCompat.cpp       \
               JIXbuttons.cpp          \
               JIXrtc.cpp              \
               JIXtimer.cpp            \
               JIXgraphics.cpp         \
               JIXmain.cpp

#---------------------------------------------------------------------
PROGRAM   = JIXsimulator
#---------------------------------------------------------------------
INCLUDESDIR     = src
SRCSDIR         = src
ARDUINODIR      = ../JIXos
DEPSDIR         = .deps
OBJSDIR         = .objs
ARDUINO_DEPSDIR = .deps_ino
ARDUINO_OBJSDIR = .objs_ino
#---------------------------------------------------------------------

CC               = g++
CPPFLAGS         = -I$(INCLUDESDIR) `sdl-config --cflags`
CFLAGS           = -Wall

ARDUINO_CPPFLAGS = $(CPPFLAGS) -include src/ArduinoCompat.h -include src/JIXhal.h -I$(ARDUINODIR)

LD = $(CC)
LDFLAGS = `sdl-config --libs`
LDLIBS = 

INO_PREPROCESS        = ino_preprocess
INO_PREPROCESS_CLASS  = utils/$(INO_PREPROCESS).class
INO_PREPROCESS_SRC    = utils/$(INO_PREPROCESS).java

INO_SRC = $(OBJSDIR)/ino_src.cpp
INO_OBJ = $(OBJSDIR)/arduino.oino

SRCS        = $(SRCSFILES:%=$(SRCSDIR)/%)
ARDUINOS    = $(ARDUINOFILES:%=$(ARDUINODIR)/%)
ARDUINOSCPP = $(ARDUINOCPP:%=$(ARDUINODIR)/%)

DEPS = $(SRCS:%.cpp=$(DEPSDIR)/%.d)
OBJS = $(SRCS:%.cpp=$(OBJSDIR)/%.o)

ARDUINOSCPP_NOTDIR = $(notdir $(ARDUINOSCPP))
ARDUINO_DEPS = $(ARDUINOSCPP_NOTDIR:%.cpp=$(ARDUINO_DEPSDIR)/%.d)
ARDUINO_OBJS = $(ARDUINOSCPP_NOTDIR:%.cpp=$(ARDUINO_OBJSDIR)/%.o)

all: $(PROGRAM)

.PHONY: clean
clean: 
	-rm -rf $(DEPSDIR) $(OBJSDIR) $(ARDUINO_DEPSDIR) $(ARDUINO_OBJSDIR) core $(PROGRAM) $(INO_PREPROCESS_CLASS)

$(INO_PREPROCESS_CLASS): $(INO_PREPROCESS_SRC)
	javac $<

$(INO_SRC): $(ARDUINOS) $(INO_PREPROCESS_CLASS)
	java -cp utils $(INO_PREPROCESS) $(ARDUINOS) > $@

$(PROGRAM):	$(DEPS) $(OBJS) $(INO_OBJ) $(ARDUINO_OBJS) $(ARDUINO_DEPS)
	$(LD) $(OBJS) $(INO_OBJ) $(ARDUINO_OBJS) $(LDFLAGS) $(LDLIBS) -o $(PROGRAM)
               
$(DEPSDIR)/%.d: %.cpp
	@ echo Making dependencies for $<
	@ mkdir -p $@ 2>/dev/null || echo "$@ already exists" >/dev/null
	@ rmdir $@ 2>/dev/null || echo "$@ already exists" >/dev/null
	@ $(CC) $(CPPFLAGS) -E -c -MM $< -o $@ >/dev/null
	@ cat $@ | sed 's#.*:# $@ :#1' > $@.tmp
	@ mv -f $@.tmp $@

$(OBJSDIR)/%.o: %.cpp $(DEPSDIR)/%.d Makefile
	@ mkdir -p $@ 2>/dev/null || echo "$@ already exists" >/dev/null
	@ rmdir $@ 2>/dev/null || echo "$@ already exists" >/dev/null
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
	
$(ARDUINO_DEPSDIR)/%.d: $(ARDUINODIR)/%.cpp
	@ echo Making dependencies for $<
	@ mkdir -p $@ 2>/dev/null || echo "$@ already exists" >/dev/null
	@ rmdir $@ 2>/dev/null || echo "$@ already exists" >/dev/null
	@ $(CC) $(ARDUINO_CPPFLAGS) -E -c -MM $< -o $@ >/dev/null
	@ cat $@ | sed 's#.*:# $@ :#1' > $@.tmp
	@ mv -f $@.tmp $@

$(ARDUINO_OBJSDIR)/%.o: $(ARDUINODIR)/%.cpp $(ARDUINO_DEPSDIR)/%.d Makefile
	@ mkdir -p $@ 2>/dev/null || echo "$@ already exists" >/dev/null
	@ rmdir $@ 2>/dev/null || echo "$@ already exists" >/dev/null
	$(CC) $(ARDUINO_CPPFLAGS) $(CFLAGS) -c $< -o $@

$(INO_OBJ): $(ARDUINOS) Makefile $(INO_SRC) src/ArduinoCompat.h src/JIXhal.h 
	@ mkdir -p $@ 2>/dev/null || echo "$@ already exists" >/dev/null
	@ rmdir $@ 2>/dev/null || echo "$@ already exists" >/dev/null
	$(CC) $(ARDUINO_CPPFLAGS) $(CFLAGS) -c $(INO_SRC) -o $@


# Include dependency files
ifneq ($(strip $(DEPS)),)
-include $(DEPS)
endif
