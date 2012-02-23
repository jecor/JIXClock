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

SRCSFILES    = JIXmain.cpp

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

INO_SRC = $(OBJSDIR)/ino_src.cpp
INO_OBJ = $(OBJSDIR)/arduino.oino

SRCS     = $(SRCSFILES:%=$(SRCSDIR)/%)
ARDUINOS = $(ARDUINOFILES:%=$(ARDUINODIR)/%)

DEPS = $(SRCS:%.cpp=$(DEPSDIR)/%.d)
OBJS = $(SRCS:%.cpp=$(OBJSDIR)/%.o)

all: $(PROGRAM)

.PHONY: clean
clean: 
	-rm -rf $(DEPSDIR) $(OBJSDIR) core $(PROGRAM) $(INO_PREPROCESS_CLASS)

$(INO_PREPROCESS_CLASS): $(INO_PREPROCESS_SRC)
	javac $<

$(INO_SRC): $(ARDUINOS) $(INO_PREPROCESS_CLASS)
	java -cp utils $(INO_PREPROCESS) $(ARDUINOS) > $@

$(PROGRAM):	$(DEPS) $(OBJS) $(INO_OBJ)
	$(LD) $(LDFLAGS) $(OBJS) $(INO_OBJ) $(LDLIBS) -o $(PROGRAM)
               
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

$(INO_OBJ): $(ARDUINOS) Makefile $(INO_SRC)
	@ mkdir -p $@ 2>/dev/null || echo "$@ already exists" >/dev/null
	@ rmdir $@ 2>/dev/null || echo "$@ already exists" >/dev/null
	$(CC) $(CPPFLAGS) $(CFLAGS) -include src/AVRcompat.h -c $(INO_SRC) -o $@


# Include dependency files
ifneq ($(strip $(DEPS)),)
-include $(DEPS)
endif
