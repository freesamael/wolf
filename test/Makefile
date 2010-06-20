BINTEST_SRCDIR = ${WOLF_TESTDIR}/bintest
UNITTEST_SRCDIR = ${WOLF_TESTDIR}/unittest
HECODSM_SRCDIR = ${WOLF_TESTDIR}/hecodsm
HECO_SRCDIR = ${WOLF_TESTDIR}/heco

include ${BINTEST_SRCDIR}/Makefile ${UNITTEST_SRCDIR}/Makefile \
	${HECODSM_SRCDIR}/Makefile ${HECO_SRCDIR}/Makefile

ifeq (${DSM}, y)
test: ${BINTEST} ${UNITTEST} ${HECODSM}
else
test: ${BINTEST} ${UNITTEST} ${HECO}
endif

test_clean: bintest_clean unittest_clean hecodsm_clean heco_clean