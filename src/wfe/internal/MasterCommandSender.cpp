/**
 * \file MasterCommandSender.cpp
 * \date May 27, 2010
 * \author samael
 */

#include "UDPSocket.h"
#include "TLVReaderWriter.h"
#include "MasterCommandSender.h"
#include "TLVCommand.h"

using namespace cml;

namespace wfe
{

void MasterCommandSender::hello(uint16_t runner_port)
{
	UDPSocket usock;
	TLVReaderWriter udprw(&usock);
	usock.setBroadcast(true);
	usock.setTTL(1);
	udprw.sendto(TLVCommand(TLVCommand::HELLO_MASTER),
	HostAddress::BroadcastAddress, runner_port);
}

void MasterCommandSender::shutdown(TCPSocket *runner)
{
	TLVCommand msg;
	msg.setCommand(TLVCommand::SHUTDOWN);

	TLVReaderWriter rw(runner);
	rw.write(msg);
}

void MasterCommandSender::runActor(TCPSocket *runner, AbstractWorkerActor *actor)
{

}

}
