#CXX = gfilt
CXX ?= ${CROSS_COMPILE}g++
AR ?= ${CROSS_COMPILE}ar

DSM ?= n
ifeq (${DSM}, y)
D2MCE_INSTDIR ?= /opt/d2mce/i386
D2MCE_INCDIR ?= ${D2MCE_INSTDIR}/include
D2MCE_LIBDIR ?= ${D2MCE_INSTDIR}/lib
CXXFLAGS += -D__D2MCE__ -I${D2MCE_INCDIR}
LDFLAGS += -L${D2MCE_LIBDIR}
D2MCE_LIBS = -ld2mce
endif

DEBUG ?= n
ifneq (${DEBUG}, n)
CXXFLAGS += -g3 -O0 -rdynamic -D__DEBUG__=${DEBUG}
else
CXXFLAGS += -O2
endif

LIBEXECINFO ?= n
ifeq (${LIBEXECINFO}, y)
CXXFLAGS += -D__USE_LIBEXECINFO
EXECINFO_LIBS = -lexecinfo
endif

COV ?= n
ifeq (${COV}, y)
CXXFLAGS += -ftest-coverage -fprofile-arcs
COV_LIBS = -lgcov
endif

CXXFLAGS += --std=c++11 -pedantic -Wall -Wextra -D_XOPEN_SOURCE=600 -D__STDC_LIMIT_MACROS

WOLF_SRCDIR = ${PWD}/src
WOLF_INCDIR = ${PWD}/include
WOLF_BINDIR = ${PWD}/bin
WOLF_LIBDIR = ${PWD}/lib
WOLF_TESTDIR = ${PWD}/test

all: -prepare-output-dirs wolf test
clean: wolf_clean test_clean
-prepare-output-dirs:
	mkdir -p ${WOLF_BINDIR}
	mkdir -p ${WOLF_LIBDIR}

include ${WOLF_SRCDIR}/Makefile
include ${WOLF_TESTDIR}/Makefile
