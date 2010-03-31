RUNNER_OBJS = ${patsubst %.cpp,%.o,${wildcard ${RUNNER_SRCDIR}/*.cpp}}
RUNNER = ${WOLF_BINDIR}/runner

${RUNNER}: CXXFLAGS += -I${COMLIB_INCDIR} -I${WOLFLIB_INCDIR} -I${D2MCE_INCDIR}
${RUNNER}: LIBS += -lpthread -ld2mce -lcom -lwolf
${RUNNER}: LDFLAGS += -L${COMLIB_SRCDIR} -L${WOLFLIB_SRCDIR} -L${D2MCE_LIBDIR}

${RUNNER}: ${RUNNER_OBJS} ${WOLFLIB} ${COMLIB}
	${CXX} -o $@ ${LDFLAGS} ${RUNNER_OBJS} ${LIBS}

runner_clean:
	-rm ${RUNNER_OBJS} ${RUNNER}
