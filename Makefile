#
# Created by gmakemake (Sparc Jul 27 2005) on Tue Nov  7 21:02:57 2006
#

#
# Definitions
#

.SUFFIXES:
.SUFFIXES:	.a .o .c .C .cpp
.c.o:
		$(COMPILE.c) $<
.C.o:
		$(COMPILE.cc) $<
.cpp.o:
		$(COMPILE.cc) $<
.c.a:
		$(COMPILE.c) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.C.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.cpp.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%

CC =		gcc
CXX =		g++

RM = rm -f
AR = ar
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c

########## Default flags (redefine these with a header.mak file if desired)
CXXFLAGS =	-ggdb -Wall
CFLAGS =	-ggdb -Wall
CLIBFLAGS =	-lm
CCLIBFLAGS =	
########## End of default flags


CPP_FILES =	 Connect3Game.cpp KaylesGame.cpp PennyPile.cpp TakeSomeGame.cpp connect3.cpp kayles.cpp takeaway.cpp takesome.cpp
C_FILES =	
H_FILES =	 Connect3Game.h Game.h GameException.h KaylesGame.h PennyPile.h Strategy.h TakeSomeGame.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	 Connect3Game.o KaylesGame.o PennyPile.o TakeSomeGame.o

#
# Main targets
#

all:	 connect3 kayles takeaway takesome 

connect3:	connect3.o $(OBJFILES)
	$(CXX) $(CXXFLAGS) -o connect3 connect3.o $(OBJFILES) $(CCLIBFLAGS)

kayles:	kayles.o $(OBJFILES)
	$(CXX) $(CXXFLAGS) -o kayles kayles.o $(OBJFILES) $(CCLIBFLAGS)

takeaway:	takeaway.o $(OBJFILES)
	$(CXX) $(CXXFLAGS) -o takeaway takeaway.o $(OBJFILES) $(CCLIBFLAGS)

takesome:	takesome.o $(OBJFILES)
	$(CXX) $(CXXFLAGS) -o takesome takesome.o $(OBJFILES) $(CCLIBFLAGS)

#
# Dependencies
#

Connect3Game.o:	 Connect3Game.h Game.h GameException.h
KaylesGame.o:	 Game.h GameException.h KaylesGame.h
PennyPile.o:	 Game.h GameException.h PennyPile.h
TakeSomeGame.o:	 Game.h GameException.h TakeSomeGame.h
connect3.o:	 Connect3Game.h Game.h GameException.h Strategy.h
kayles.o:	 Game.h GameException.h KaylesGame.h Strategy.h
takeaway.o:	 Game.h GameException.h PennyPile.h Strategy.h
takesome.o:	 Game.h GameException.h Strategy.h TakeSomeGame.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -r $(OBJFILES) connect3.o kayles.o takeaway.o takesome.o core 2> /dev/null

realclean:        clean
	/bin/rm -rf  connect3 kayles takeaway takesome 
