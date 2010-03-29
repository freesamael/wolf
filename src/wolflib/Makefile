WOLFLIB_OBJS = ${WOLFLIB_SRCDIR}/AbstractManagerActor.o \
${WOLFLIB_SRCDIR}/Channel.o ${WOLFLIB_SRCDIR}/Director.o \
${WOLFLIB_SRCDIR}/Port.o ${WOLFLIB_SRCDIR}/SimpleExecutionStrategy.o \
${WOLFLIB_SRCDIR}/IActor.o ${WOLFLIB_SRCDIR}/TLVMessage.o

WOLFLIB = ${WOLFLIB_SRCDIR}/libwolf.a

${WOLFLIB}: ${WOLFLIB_OBJS}
	${AR} rvs $@ $^

wolflib_clean:
	-rm ${WOLFLIB_OBJS} ${WOLFLIB}

