COMLIB_SRCDIR = ${WOLF_SRCDIR}/comlib
WOLFLIB_SRCDIR = ${WOLF_SRCDIR}/wolflib
WOLFEXEC_SRCDIR = ${WOLF_SRCDIR}/wolfexec
WOLF_INCDIR = ${WOLF_SRCDIR}/include

CPPFLAGS+= -I${WOLF_INCDIR} 

include ${COMLIB_SRCDIR}/Makefile ${WOLFLIB_SRCDIR}/Makefile ${WOLFEXEC_SRCDIR}/Makefile

wolf: ${COMLIB} ${WOLFLIB} ${WOLFEXEC}

clean: comlib_clean wolflib_clean wolfexec_clean

