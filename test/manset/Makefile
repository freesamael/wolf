MANSET = ${WOLF_BINDIR}/manset
MANSET_O = ${MANSET_SRCDIR}/manset.o
MANSET_RUNNER = ${WOLF_BINDIR}/manset_runner
MANSET_RUNNER_O = ${MANSET_SRCDIR}/manset_runner.o
MANSET_COM_OBJS := ${filter-out ${MANSET_O} ${MANSET_RUNNER_O},${patsubst %.cpp,%.o,${wildcard ${MANSET_SRCDIR}/*.cpp}}}

${MANSET}: CXXFLAGS += -I${WOLF_INCDIR} -I/usr/include/opencv
${MANSET}: LIBS += -lwolf -lpthread -lopencv_core -lopencv_highgui ${EXECINFO_LIBS} ${COV_LIBS}
${MANSET}: LDFLAGS += -L${WOLF_LIBDIR}

${MANSET}: ${MANSET_O} ${MANSET_COM_OBJS} ${MANSET_RUNNER}
	${CXX} ${CXXFLAGS} -o $@ ${LDFLAGS} ${MANSET_O} ${MANSET_COM_OBJS} ${LIBS}

${MANSET_RUNNER}: ${MANSET_RUNNER_O} ${MANSET_COM_OBJS} ${WOLF}
	${CXX} ${CXXFLAGS} -o $@ ${LDFLAGS} ${MANSET_RUNNER_O} ${MANSET_COM_OBJS} ${LIBS}

manset_clean:
	-rm ${MANSET} ${MANSET_O} ${MANSET_RUNNER} ${MANSET_RUNNER_O} ${MANSET_COM_OBJS}
