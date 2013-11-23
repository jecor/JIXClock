# 
# JIXClock SDK  
# Copyright (c) 2012-2013 JŽr™me Cornet
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

ARDUINOINO      = JIXos.ino

ARDUINOCPP      = JIXColorTestMode.cpp    \
                  JIXColorfulMode.cpp     \
                  JIXModeDisplay.cpp      \
                  JIXRainbowMode.cpp      \
                  JIXSecondsBlinkMode.cpp \
                  JIXSecondsMode.cpp      \
                  JIXSplash.cpp           \
                  JIXStandardMode.cpp     \
                  JIXTorchMode.cpp        \
                  JIXDemoMode.cpp

SRCSFILES       = ArduinoCompat.cpp       \
                  JIXbuttons.cpp          \
                  JIXrtc.cpp              \
                  JIXtimer.cpp            \
                  JIXgraphics.cpp         \
                  JIXmain.cpp

#---------------------------------------------------------------------

PROGRAM         = JIXsimulator

#---------------------------------------------------------------------

INCLUDESDIR        = src
SRCSDIR            = src
ARDUINODIR         = ../JIXos

DEPSDIR            = .deps
OBJSDIR            = .objs

ARDUINOCPP_DEPSDIR = .deps_ino_cpp
ARDUINOCPP_OBJSDIR = .objs_ino_cpp

ARDUINOINO_DEPSDIR = .deps_ino
ARDUINOINO_OBJSDIR = .objs_ino

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

SRCS         = $(SRCSFILES:%=$(SRCSDIR)/%)

DEPS         = $(SRCS:%.cpp=$(DEPSDIR)/%.d)
OBJS         = $(SRCS:%.cpp=$(OBJSDIR)/%.o)

ARDUINOCPP_DEPS = $(ARDUINOCPP:%.cpp=$(ARDUINOCPP_DEPSDIR)/%.d)
ARDUINOCPP_OBJS = $(ARDUINOCPP:%.cpp=$(ARDUINOCPP_OBJSDIR)/%.o)

ARDUINOINO_DEPS = $(ARDUINOINO:%.ino=$(ARDUINOINO_DEPSDIR)/%.d)
ARDUINOINO_OBJS = $(ARDUINOINO:%.ino=$(ARDUINOINO_OBJSDIR)/%.o)

all: $(PROGRAM)

.PHONY: clean
clean: 
	-rm -rf $(DEPSDIR) $(OBJSDIR) $(ARDUINOCPP_DEPSDIR) $(ARDUINOCPP_OBJSDIR) \
	        $(ARDUINOINO_DEPSDIR) $(ARDUINOINO_OBJSDIR)core $(PROGRAM) $(INO_PREPROCESS_CLASS)

$(INO_PREPROCESS_CLASS): $(INO_PREPROCESS_SRC)
	javac $<

$(INO_SRC): $(ARDUINO) $(INO_PREPROCESS_CLASS)
#	java -cp utils $(INO_PREPROCESS) $(ARDUINOS) > $@
	cat $(ARDUINODIR)/$(ARDUINOINO) > $@

$(PROGRAM):	$(DEPS) $(OBJS) $(ARDUINOCPP_OBJS) $(ARDUINOCPP_DEPS) $(ARDUINOINO_OBJS) $(ARDUINOINO_DEPS)
	$(LD) $(OBJS) $(ARDUINOCPP_OBJS) $(ARDUINOINO_OBJS) $(LDFLAGS) $(LDLIBS) -o $(PROGRAM)
               
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
	
$(ARDUINOCPP_DEPSDIR)/%.d: $(ARDUINODIR)/%.cpp
	@ echo Making dependencies for $<
	@ mkdir -p $@ 2>/dev/null || echo "$@ already exists" >/dev/null
	@ rmdir $@ 2>/dev/null || echo "$@ already exists" >/dev/null
	@ $(CC) $(ARDUINO_CPPFLAGS) -E -c -MM $< -o $@ >/dev/null
	@ cat $@ | sed 's#.*:# $@ :#1' > $@.tmp
	@ mv -f $@.tmp $@

$(ARDUINOCPP_OBJSDIR)/%.o: $(ARDUINODIR)/%.cpp $(ARDUINOCPP_DEPSDIR)/%.d src/ArduinoCompat.h src/JIXhal.h Makefile
	@ mkdir -p $@ 2>/dev/null || echo "$@ already exists" >/dev/null
	@ rmdir $@ 2>/dev/null || echo "$@ already exists" >/dev/null
	$(CC) $(ARDUINO_CPPFLAGS) $(CFLAGS) -c $< -o $@
	
$(ARDUINOINO_DEPSDIR)/%.d: $(ARDUINODIR)/%.ino
	@ echo Making dependencies for $<
	@ mkdir -p $@ 2>/dev/null || echo "$@ already exists" >/dev/null
	@ rmdir $@ 2>/dev/null || echo "$@ already exists" >/dev/null
	@ $(CC) $(ARDUINO_CPPFLAGS) -x c++ -E -c -MM $< -o $@ >/dev/null
	@ cat $@ | sed 's#.*:# $@ :#1' > $@.tmp
	@ mv -f $@.tmp $@

$(ARDUINOINO_OBJSDIR)/%.o: $(ARDUINODIR)/%.ino $(ARDUINOINO_DEPSDIR)/%.d src/ArduinoCompat.h src/JIXhal.h Makefile
	@ mkdir -p $@ 2>/dev/null || echo "$@ already exists" >/dev/null
	@ rmdir $@ 2>/dev/null || echo "$@ already exists" >/dev/null
	$(CC) $(ARDUINO_CPPFLAGS) $(CFLAGS) -x c++ -c $< -o $@

# Include dependency files
ifneq ($(strip $(DEPS)),)
-include $(DEPS)
endif
