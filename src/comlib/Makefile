COMLIB_OBJS := ${patsubst %.cpp,%.o,${wildcard ${COMLIB_SRCDIR}/*.cpp}}
COMLIB = ${COMLIB_SRCDIR}/libcom.a
${COMLIB}: CXXFLAGS += -I${COMLIB_INCDIR}

${COMLIB}: ${COMLIB_OBJS}
	${AR} rvs $@ $^

comlib_clean:
	-rm ${COMLIB_OBJS} ${COMLIB}

