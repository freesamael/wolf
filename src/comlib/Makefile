COMLIB_OBJS := ${patsubst %.cpp,%.o,${wildcard ${COMLIB_SRCDIR}/*.cpp}}
COMLIB = ${COMLIB_SRCDIR}/libwolfcom.a
${COMLIB}: CXXFLAGS += -I${COMLIB_INCDIR} -I${D2MCE_INCDIR}

${COMLIB}: ${COMLIB_OBJS}
	${AR} rvs $@ $^

comlib_clean:
	-rm ${COMLIB_OBJS} ${COMLIB}
