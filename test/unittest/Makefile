UNITTEST_OBJS := ${patsubst %.cpp,%.o,${wildcard ${UNITTEST_SRCDIR}/*.cpp}}
UNITTEST = ${WOLF_BINDIR}/unittest
${UNITTEST}: CXXFLAGS += -I${COMLIB_INCDIR} -I${WOLFLIB_INCDIR} -I${D2MCE_INCDIR}
${UNITTEST}: LIBS += -lwolf -ld2mce -lpthread -lcppunit
${UNITTEST}: LDFLAGS += -L${WOLF_LIBDIR} -L${D2MCE_LIBDIR}

${UNITTEST}: ${UNITTEST_OBJS} ${WOLFLIB}
	${CXX} ${CXXFLAGS} -o $@ ${LDFLAGS} ${UNITTEST_OBJS} ${LIBS}

unittest_clean:
	-rm ${UNITTEST} ${UNITTEST_OBJS}
