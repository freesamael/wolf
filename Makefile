#CXX = gfilt
CXX ?= ${CROSS_COMPILE}g++
AR ?= ${CROSS_COMPILE}ar

DSM ?= yes

ifeq (${DSM}, yes)
D2MCE_INSTDIR ?= /opt/d2mce/i386
D2MCE_INCDIR ?= ${D2MCE_INSTDIR}/include
D2MCE_LIBDIR ?= ${D2MCE_INSTDIR}/lib
D2MCE_CXXFLAGS = -I${D2MCE_INCDIR}
D2MCE_LDFLAGS = -L${D2MCE_LIBDIR}
D2MCE_LIBS = -ld2mce
else
CXXFLAGS += -DDISABLE_D2MCE
endif

CXXFLAGS += -g3 -O0 -ansi -pedantic -Wall -Wextra -Wabi -Wctor-dtor-privacy \
-Wnon-virtual-dtor -Wstrict-null-sentinel -Woverloaded-virtual -Wsign-promo \
-Wformat=2 -Winit-self -Wmissing-include-dirs -Wswitch-default -Wswitch-enum \
-Wfloat-equal -Wlarger-than=128 -Wcast-qual -Wcast-align -Wlogical-op \
-Wmissing-declarations -Winline -Woverlength-strings 

WOLF_SRCDIR = ${PWD}/src
WOLF_BINDIR = ${PWD}/bin
WOLF_LIBDIR = ${PWD}/lib
WOLF_TESTDIR = ${PWD}/test

all: wolf test
clean: wolf_clean test_clean

include ${WOLF_SRCDIR}/Makefile
include ${WOLF_TESTDIR}/Makefile
