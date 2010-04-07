HECO = ${WOLF_BINDIR}/heco
HECO_O = ${HECO_SRCDIR}/heco.o
HECO_RUNNER = ${WOLF_BINDIR}/heco_runner
HECO_RUNNER_O = ${HECO_SRCDIR}/heco_runner.o
HECO_COM_OBJS := ${filter-out ${HECO_O} ${HECO_RUNNER_O},${patsubst %.cpp,%.o,${wildcard ${HECO_SRCDIR}/*.cpp}}}

${HECO}: CXXFLAGS += -I${COMLIB_INCDIR} -I${WOLFLIB_INCDIR} -I${D2MCE_INCDIR}
${HECO}: LIBS += -lwolf -ld2mce -lpthread
${HECO}: LDFLAGS += -L${WOLF_LIBDIR} -L${D2MCE_LIBDIR}

${HECO}: ${HECO_O} ${HECO_COM_OBJS} ${HECO_RUNNER}
	${CXX} -o $@ ${LDFLAGS} ${HECO_O} ${HECO_COM_OBJS} ${LIBS}

${HECO_RUNNER}: ${HECO_RUNNER_O} ${HECO_COM_OBJS}
	${CXX} -o $@ ${LDFLAGS} ${HECO_RUNNER_O} ${HECO_COM_OBJS}

heco_clean:
	-rm ${HECO} ${HECO_O} ${HECO_RUNNER} ${HECO_RUNNER_O} ${HECO_COM_OBJS}