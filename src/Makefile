COMLIB_SRCDIR = ${WOLF_SRCDIR}/cml
COMLIB_INCDIR = ${WOLF_SRCDIR}/cmlhdr
WOLFLIB_SRCDIR = ${WOLF_SRCDIR}/wfe
WOLFLIB_INCDIR = ${WOLF_SRCDIR}/wfehdr

include ${COMLIB_SRCDIR}/Makefile ${WOLFLIB_SRCDIR}/Makefile 

wolf: ${COMLIB} ${WOLFLIB}

wolf_clean: comlib_clean wolflib_clean 
