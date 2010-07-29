HECO = ${WOLF_BINDIR}/heco
HECO_O = ${HECO_SRCDIR}/heco.o
HECO_RUNNER = ${WOLF_BINDIR}/heco_runner
HECO_RUNNER_O = ${HECO_SRCDIR}/heco_runner.o
HECO_COM_OBJS := ${filter-out ${HECO_O} ${HECO_RUNNER_O},${patsubst %.cpp,%.o,${wildcard ${HECO_SRCDIR}/*.cpp}}}

${HECO}: CXXFLAGS += -I${WOLF_INCDIR}
${HECO}: LIBS += -lwolf -lpthread ${EXECINFO_LIBS} ${COV_LIBS}
${HECO}: LDFLAGS += -L${WOLF_LIBDIR}

${HECO}: ${HECO_O} ${HECO_COM_OBJS} ${HECO_RUNNER}
	${CXX} ${CXXFLAGS} -o $@ ${LDFLAGS} ${HECO_O} ${HECO_COM_OBJS} ${LIBS}

${HECO_RUNNER}: ${HECO_RUNNER_O} ${HECO_COM_OBJS} ${WOLF}
	${CXX} ${CXXFLAGS} -o $@ ${LDFLAGS} ${HECO_RUNNER_O} ${HECO_COM_OBJS} ${LIBS}

heco_clean:
	-rm ${HECO} ${HECO_O} ${HECO_RUNNER} ${HECO_RUNNER_O} ${HECO_COM_OBJS}