COMLIB_SRCDIR = ${WOLF_SRCDIR}/comlib
COMLIB_INCDIR = ${WOLF_SRCDIR}/comlibinc
WOLFLIB_SRCDIR = ${WOLF_SRCDIR}/wolflib
WOLFLIB_INCDIR = ${WOLF_SRCDIR}/wolflibinc
BINTEST_SRCDIR = ${WOLF_SRCDIR}/bintest
UNITTEST_SRCDIR = ${WOLF_SRCDIR}/unittest
RUNNER_SRCDIR = ${WOLF_SRCDIR}/runner

include ${COMLIB_SRCDIR}/Makefile ${WOLFLIB_SRCDIR}/Makefile \
${BINTEST_SRCDIR}/Makefile ${UNITTEST_SRCDIR}/Makefile \
${RUNNER_SRCDIR}/Makefile

wolf: ${COMLIB} ${WOLFLIB} ${RUNNER}

test: ${BINTEST} ${UNITTEST}

clean: comlib_clean wolflib_clean bintest_clean unittest_clean runner_clean
