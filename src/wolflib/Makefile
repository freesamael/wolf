WOLFLIB_OBJS := ${patsubst %.cpp,%.o,${wildcard ${WOLFLIB_SRCDIR}/*.cpp}}
WOLFLIB = ${WOLF_LIBDIR}/libwolf.a
${WOLFLIB}: CXXFLAGS += -I${COMLIB_INCDIR} -I${WOLFLIB_INCDIR} -I${D2MCE_INCDIR}

${WOLFLIB}: ${WOLFLIB_OBJS} ${COMLIB}
	${AR} cru $@ ${WOLFLIB_OBJS} ${COMLIB_OBJS}

wolflib_clean:
	-rm ${WOLFLIB_OBJS} ${WOLFLIB}
