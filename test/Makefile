BINTEST_SRCDIR = ${WOLF_TESTDIR}/bintest
UNITTEST_SRCDIR = ${WOLF_TESTDIR}/unittest
HECO_SRCDIR = ${WOLF_TESTDIR}/heco

include ${BINTEST_SRCDIR}/Makefile ${UNITTEST_SRCDIR}/Makefile \
	${HECO_SRCDIR}/Makefile

test: ${BINTEST} ${UNITTEST} ${HECO}

test_clean: bintest_clean unittest_clean heco_clean