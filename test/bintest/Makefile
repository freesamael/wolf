BINTEST_OBJS := ${patsubst %.cpp,%.o,${wildcard ${BINTEST_SRCDIR}/*.cpp}}
BINTEST := ${addprefix ${WOLF_BINDIR}/,${notdir ${basename ${BINTEST_OBJS}}}}
${BINTEST}: CXXFLAGS += -I${WOLF_INCDIR}
${BINTEST}: LIBS += -lwolf -lpthread ${D2MCE_LIBS} ${EXECINFO_LIBS} ${COV_LIBS}
${BINTEST}: LDFLAGS += -L${WOLF_LIBDIR}

${BINTEST}: ${BINTEST_OBJS} ${WOLF}
	${CXX} ${CXXFLAGS} -o $@ ${LDFLAGS} ${BINTEST_SRCDIR}/${@F}.o ${LIBS}

bintest_clean:
	-rm ${BINTEST_OBJS} ${BINTEST}
