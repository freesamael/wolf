#CXX = gfilt
CXX ?= ${CROSS_COMPILE}g++
AR ?= ${CROSS_COMPILE}ar

D2MCE_INSTDIR ?= /opt/d2mce/i386
D2MCE_INCDIR ?= ${D2MCE_INSTDIR}/include
D2MCE_LIBDIR ?= ${D2MCE_INSTDIR}/lib
CXXFLAGS += -g3 -O0 -Wall

WOLF_SRCDIR = ${PWD}/src
WOLF_BINDIR = ${PWD}/bin

all: wolf

include ${WOLF_SRCDIR}/Makefile

