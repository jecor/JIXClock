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
SRCSFILES    = JIXmain.cpp
ARDUINOFILES = JIXos.ino               \
               JIXColorTestMode.ino    \
               JIXColorfulMode.ino     \
               JIXModeDisplay.ino      \
               JIXRainbowMode.ino      \
               JIXSecondsBlinkMode.ino \
               JIXSecondsMode.ino      \
               JIXSplash.ino           \
               JIXStandardMode.ino     \
               JIXTorchMode.ino
               
#---------------------------------------------------------------------
PROGRAM   = JIXsimulator
#---------------------------------------------------------------------
INCLUDESDIR = src
SRCSDIR     = src
ARDUINODIR  = ../JIXos
DEPSDIR     = .deps
OBJSDIR     = .objs
#---------------------------------------------------------------------

CC = g++
CPPFLAGS = -I$(INCLUDESDIR) `sdl-config --cflags`
CFLAGS   = -Wall

LD = $(CC)
LDFLAGS = `sdl-config --libs`
LDLIBS = 

INO_PREPROCESS        = ino_preprocess
INO_PREPROCESS_CLASS  = utils/$(INO_PREPROCESS).class
INO_PREPROCESS_SRC    = utils/$(INO_PREPROCESS).java

INO_HEADER =  $(OBJSDIR)/ino_header.h

SRCS     = $(SRCSFILES:%=$(SRCSDIR)/%)
ARDUINOS = $(ARDUINOFILES:%=$(ARDUINODIR)/%)

DEPS = $(SRCS:%.cpp=$(DEPSDIR)/%.d)
OBJS = $(SRCS:%.cpp=$(OBJSDIR)/%.o)

OBJARDUINO = $(OBJSDIR)/arduino.oino

all: $(PROGRAM)

.PHONY: clean
clean: 
	-rm -rf $(DEPSDIR) $(OBJSDIR) core $(PROGRAM) $(INO_PREPROCESS_CLASS) $(INO_HEADER)

$(INO_PREPROCESS_CLASS): $(INO_PREPROCESS_SRC)
	javac $<

$(INO_HEADER): $(ARDUINOS) $(INO_PREPROCESS_CLASS)
	java -cp utils $(INO_PREPROCESS) $(ARDUINOS) > $(INO_HEADER)

$(PROGRAM):	$(DEPS) $(OBJS) $(OBJARDUINO)
	$(LD) $(LDFLAGS) $(OBJS) $(OBJARDUINO) $(LDLIBS) -o $(PROGRAM)
               
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

$(OBJARDUINO): $(ARDUINOS) Makefile $(INO_HEADER)
	@ mkdir -p $@ 2>/dev/null || echo "$@ already exists" >/dev/null
	@ rmdir $@ 2>/dev/null || echo "$@ already exists" >/dev/null
	cat $(ARDUINOS) > $(OBJSDIR)/inosrc.cpp
	$(CC) $(CPPFLAGS) $(CFLAGS) -include src/AVRcompat.h -include $(INO_HEADER) -c $(OBJSDIR)/inosrc.cpp -o $@


# Include dependency files
ifneq ($(strip $(DEPS)),)
-include $(DEPS)
endif
