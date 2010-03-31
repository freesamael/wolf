COMLIB_SRCDIR = ${WOLF_SRCDIR}/comlib
COMLIB_INCDIR = ${WOLF_SRCDIR}/comlibinc
WOLFLIB_SRCDIR = ${WOLF_SRCDIR}/wolflib
WOLFLIB_INCDIR = ${WOLF_SRCDIR}/wolflibinc
WOLFEXEC_SRCDIR = ${WOLF_SRCDIR}/wolfexec
UNITTEST_SRCDIR = ${WOLF_SRCDIR}/unittest

include ${COMLIB_SRCDIR}/Makefile ${WOLFLIB_SRCDIR}/Makefile \
${WOLFEXEC_SRCDIR}/Makefile ${UNITTEST_SRCDIR}/Makefile

wolf: ${COMLIB} ${WOLFLIB} ${WOLFEXECS}

test: ${UNITTEST}

clean: comlib_clean wolflib_clean wolfexec_clean unittest_clean
