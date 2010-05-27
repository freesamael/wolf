/**
 * \file TLVCommand.h
 * \date Mar 29, 2010
 * \author samael
 */

#ifndef TLVCOMMAND_H_
#define TLVCOMMAND_H_

#include <string>
#include <stdint.h>
#include "ITLVObject.h"

namespace wfe
{

/**
 * TLVCommand represents the command used for communications between runners
 * and master.
 */
class TLVCommand: public cml::ITLVObject
{
public:
	static const uint16_t TLVType;
	/**
	 * Enumeration of commands. To ensure the size and value of commands, we
	 * use constant uint16_t instead of C++ 'enum' here.
	 */
	static const std::string CommandString[];
	static const uint16_t EMPTY;
	static const uint16_t SHUTDOWN;
	static const uint16_t HELLO_MASTER;
	static const uint16_t HELLO_RUNNER;
	static const uint16_t ACTOR_RUN;
	static const uint16_t ACTOR_FINISHED;
	static const uint16_t RUNNER_ADD;
	static const uint16_t RUNNER_START;

	TLVCommand(uint16_t c = EMPTY): _cmd(c){}
	inline uint16_t command() const { return _cmd; }
	inline void setCommand(uint16_t c) { _cmd = c; }
	virtual cml::StandardTLVBlock* toTLVBlock() const;

private:
	uint16_t _cmd;
};

}

#endif /* TLVCOMMAND_H_ */
