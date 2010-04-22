COMLIB_OBJS := ${patsubst %.cpp,%.o,${wildcard ${COMLIB_SRCDIR}/*.cpp ${COMLIB_SRCDIR}/private/*.cpp}}
COMLIB = ${WOLF_LIBDIR}/libcom.a
${COMLIB}: CXXFLAGS += -I${COMLIB_INCDIR} ${D2MCE_CXXFLAGS}

${COMLIB}: ${COMLIB_OBJS}
	${AR} cru $@ $^

comlib_clean:
	-rm ${COMLIB_OBJS} ${COMLIB}
