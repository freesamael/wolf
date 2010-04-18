BINTEST_OBJS := ${patsubst %.cpp,%.o,${wildcard ${BINTEST_SRCDIR}/*.cpp}}
BINTEST := ${addprefix ${WOLF_BINDIR}/,${notdir ${basename ${BINTEST_OBJS}}}}
${BINTEST}: CXXFLAGS += -I${COMLIB_INCDIR} -I${WOLFLIB_INCDIR} ${D2MCE_CXXFLAGS}
${BINTEST}: LIBS += -lwolf -lpthread ${D2MCE_LIBS}
${BINTEST}: LDFLAGS += -L${WOLF_LIBDIR} ${D2MCE_LDFLAGS}

${BINTEST}: ${BINTEST_OBJS} ${WOLFLIB}
	${CXX} ${CXXFLAGS} -o $@ ${LDFLAGS} ${BINTEST_SRCDIR}/${@F}.o ${LIBS}

bintest_clean:
	-rm ${BINTEST_OBJS} ${BINTEST}
