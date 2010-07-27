WOLF_OBJS := ${patsubst %.cpp,%.o,${wildcard ${WOLF_SRCDIR}/*.cpp ${WOLF_SRCDIR}/internal/*.cpp}}
WOLF = ${WOLF_LIBDIR}/libwolf.a
${WOLF}: CXXFLAGS += -Weffc++ -I${WOLF_INCDIR} ${D2MCE_CXXFLAGS}

wolf: ${WOLF_OBJS}
	${AR} cru $@ ${WOLF_OBJS}

wolf_clean: 
	-rm ${WOLF_OBJS} ${WOLF} 
