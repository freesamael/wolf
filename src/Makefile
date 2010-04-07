COMLIB_SRCDIR = ${WOLF_SRCDIR}/comlib
COMLIB_INCDIR = ${WOLF_SRCDIR}/comlibinc
WOLFLIB_SRCDIR = ${WOLF_SRCDIR}/wolflib
WOLFLIB_INCDIR = ${WOLF_SRCDIR}/wolflibinc

include ${COMLIB_SRCDIR}/Makefile ${WOLFLIB_SRCDIR}/Makefile 

wolf: ${COMLIB} ${WOLFLIB}

wolf_clean: comlib_clean wolflib_clean 
