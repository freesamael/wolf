UNITTEST_OBJS = ${UNITTEST_SRCDIR}/main.o \
${UNITTEST_SRCDIR}/ProcessEnvironmentTestSuite.o \
${UNITTEST_SRCDIR}/ProcessTestSuite.o \
${UNITTEST_SRCDIR}/StringHelperTestSuite.o \
${UNITTEST_SRCDIR}/TLVStringCreatorTestSuite.o \
${UNITTEST_SRCDIR}/TLVStringTestSuite.o
 
UNITTEST = ${WOLF_BINDIR}/unittest

LIBS += -lcppunit

${UNITTEST}: ${UNITTEST_OBJS} ${WOLFLIB} ${COMLIB}
	${CXX} -o $@ ${LDFLAGS} $^ ${LIBS}

unittest_clean:
	-rm ${UNITTEST} ${UNITTEST_OBJS}

