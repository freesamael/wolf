/**
 * \file TLVMessage.h
 * \date Mar 29, 2010
 * \author samael
 */

#ifndef TLVMESSAGE_H_
#define TLVMESSAGE_H_

#include <stdint.h>
#include "ITLVObject.h"

namespace wfe
{

/**
 * @note TLVMessage takes the ownership of parameter, and deletes it on
 * destruction.
 */
class TLVMessage: public cml::ITLVObject
{
public:
	static const uint16_t TLVType;
	/**
	 * Enumeration of commands. To ensure the size and value of commands, we
	 * use constant uint16_t instead of C++ 'enum' here.
	 */
	static const char *CommandString[];
	static const uint16_t EMPTY;
	static const uint16_t SHUTDOWN;
	static const uint16_t HELLO_MASTER;
	static const uint16_t HELLO_SLAVE;
	static const uint16_t ACTOR_RUN;
	static const uint16_t ACTOR_FINISHED;

	TLVMessage(uint16_t c = EMPTY, ITLVObject *param = NULL):
		_cmd(c), _param(param) {}
	TLVMessage(const TLVMessage &msg):
		_cmd(msg._cmd), _param(msg._param) {}
	TLVMessage& operator=(const TLVMessage &msg)
		{ _cmd = msg._cmd; _param = msg._param; return *this; }
	inline uint16_t command() const { return _cmd; }
	inline ITLVObject* parameter() const { return _param; }
	inline void setCommand(uint16_t c) { _cmd = c; }
	inline void setParameter(ITLVObject *param) { _param = param; }
	cml::StandardTLVBlock* toTLVBlock() const;

private:
	uint16_t _cmd;
	ITLVObject *_param;
};

}

#endif /* TLVMESSAGE_H_ */
