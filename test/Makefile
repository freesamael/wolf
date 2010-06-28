BINTEST_SRCDIR = ${WOLF_TESTDIR}/bintest
UNITTEST_SRCDIR = ${WOLF_TESTDIR}/unittest
HECODSM_SRCDIR = ${WOLF_TESTDIR}/hecodsm
HECO_SRCDIR = ${WOLF_TESTDIR}/heco
MSORT_SRCDIR = ${WOLF_TESTDIR}/msort

include ${BINTEST_SRCDIR}/Makefile ${UNITTEST_SRCDIR}/Makefile \
	${HECODSM_SRCDIR}/Makefile ${HECO_SRCDIR}/Makefile ${MSORT_SRCDIR}/Makefile

ifeq (${DSM}, y)
test: ${BINTEST} ${UNITTEST} ${HECODSM}
else
test: ${BINTEST} ${UNITTEST} ${HECO} ${MSORT}
endif

test_clean: bintest_clean unittest_clean hecodsm_clean heco_clean msort_clean