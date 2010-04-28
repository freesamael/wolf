WOLFLIB_OBJS := ${patsubst %.cpp,%.o,${wildcard ${WOLFLIB_SRCDIR}/*.cpp ${WOLFLIB_SRCDIR}/private/*.cpp}}
WOLFLIB = ${WOLF_LIBDIR}/libwolf.a
${WOLFLIB}: CXXFLAGS += -Weffc++ -I${COMLIB_INCDIR} -I${WOLFLIB_INCDIR} ${D2MCE_CXXFLAGS}

${WOLFLIB}: ${WOLFLIB_OBJS} ${COMLIB}
	${AR} cru $@ ${WOLFLIB_OBJS} ${COMLIB_OBJS}

wolflib_clean:
	-rm ${WOLFLIB_OBJS} ${WOLFLIB}
