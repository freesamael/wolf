WOLFOBJS := ${patsubst %.cpp,%.o,${wildcard ${WOLFEXEC_SRCDIR}/*.cpp}}
WOLFEXECS := ${addprefix ${WOLF_BINDIR}/,${notdir ${basename ${WOLFOBJS}}}}
${WOLFEXECS}: CXXFLAGS += -I${COMLIB_INCDIR} -I${WOLFLIB_INCDIR} -I${D2MCE_INCDIR}
${WOLFEXECS}: LIBS += -lpthread -ld2mce -lcom -lwolf
${WOLFEXECS}: LDFLAGS += -L${COMLIB_SRCDIR} -L${WOLFLIB_SRCDIR} -L${D2MCE_LIBDIR}

${WOLFEXECS}: ${WOLFOBJS}
	${CXX} -o $@ ${LDFLAGS} ${WOLFEXEC_SRCDIR}/${@F}.o ${LIBS}

wolfexec_clean:
	-rm ${WOLFOBJS} ${WOLFEXECS}
