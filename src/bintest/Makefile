BINTEST_OBJS := ${patsubst %.cpp,%.o,${wildcard ${BINTEST_SRCDIR}/*.cpp}}
BINTEST := ${addprefix ${WOLF_BINDIR}/,${notdir ${basename ${BINTEST_OBJS}}}}
${BINTEST}: CXXFLAGS += -I${COMLIB_INCDIR} -I${WOLFLIB_INCDIR} -I${D2MCE_INCDIR}
${BINTEST}: LIBS += -lwolf -ld2mce -lpthread
${BINTEST}: LDFLAGS += -L${WOLF_LIBDIR} -L${D2MCE_LIBDIR}

${BINTEST}: ${BINTEST_OBJS} ${WOLFLIB}
	${CXX} -o $@ ${LDFLAGS} ${BINTEST_SRCDIR}/${@F}.o ${LIBS}

bintest_clean:
	-rm ${BINTEST_OBJS} ${BINTEST}
