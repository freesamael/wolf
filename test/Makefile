BINTEST_SRCDIR = ${WOLF_TESTDIR}/bintest
UNITTEST_SRCDIR = ${WOLF_TESTDIR}/unittest
HECODSM_SRCDIR = ${WOLF_TESTDIR}/hecodsm

include ${BINTEST_SRCDIR}/Makefile ${UNITTEST_SRCDIR}/Makefile \
	${HECODSM_SRCDIR}/Makefile

ifeq (${DSM}, y)
test: ${BINTEST} ${UNITTEST} ${HECODSM}
else
test: ${BINTEST} ${UNITTEST}
endif

test_clean: bintest_clean unittest_clean hecodsm_clean