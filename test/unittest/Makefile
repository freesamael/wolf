UNITTEST_OBJS := ${patsubst %.cpp,%.o,${wildcard ${UNITTEST_SRCDIR}/*.cpp}}
UNITTEST = ${WOLF_BINDIR}/unittest
${UNITTEST}: CXXFLAGS += -I${WOLF_INCDIR}
${UNITTEST}: LIBS += -lwolf -lpthread -lcppunit ${D2MCE_LIBS} ${EXECINFO_LIBS} ${COV_LIBS}
${UNITTEST}: LDFLAGS += -L${WOLF_LIBDIR}

${UNITTEST}: ${UNITTEST_OBJS} ${WOLF}
	${CXX} ${CXXFLAGS} -o $@ ${LDFLAGS} ${UNITTEST_OBJS} ${LIBS}

unittest_clean:
	-rm ${UNITTEST} ${UNITTEST_OBJS}
