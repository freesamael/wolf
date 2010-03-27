COMLIB_OBJS = ${COMLIB_SRCDIR}/AbstractSocket.o ${COMLIB_SRCDIR}/ProcessEnvironment.o ${COMLIB_SRCDIR}/TCPSocket.o ${COMLIB_SRCDIR}/TLVReaderWriter.o ${COMLIB_SRCDIR}/D2MCE.o ${COMLIB_SRCDIR}/SharedMemory.o ${COMLIB_SRCDIR}/Thread.o ${COMLIB_SRCDIR}/TLVString.o ${COMLIB_SRCDIR}/HostAddress.o ${COMLIB_SRCDIR}/StringHelper.o ${COMLIB_SRCDIR}/TLVBlock.o ${COMLIB_SRCDIR}/TLVStringCreator.o ${COMLIB_SRCDIR}/Process.o ${COMLIB_SRCDIR}/TCPServer.o ${COMLIB_SRCDIR}/TLVObjectFactory.o ${COMLIB_SRCDIR}/UDPSocket.o

COMLIB = ${COMLIB_SRCDIR}/libcom.a

${COMLIB}: ${COMLIB_OBJS}
	${AR} rvs $@ $^

comlib_clean:
	-rm ${COMLIB_OBJS} ${COMLIB}

