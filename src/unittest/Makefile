UNITTEST_OBJS := ${patsubst %.cpp,%.o,${wildcard ${UNITTEST_SRCDIR}/*.cpp}}
UNITTEST = ${WOLF_BINDIR}/unittest
${UNITTEST}: CXXFLAGS += -I${COMLIB_INCDIR} -I${WOLFLIB_INCDIR} -I${D2MCE_INCDIR}
${UNITTEST}: LIBS += -lcppunit

${UNITTEST}: ${UNITTEST_OBJS} ${WOLFLIB} ${COMLIB}
	${CXX} -o $@ ${LDFLAGS} $^ ${LIBS}

unittest_clean:
	-rm ${UNITTEST} ${UNITTEST_OBJS}
