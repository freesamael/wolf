/**
 * \file TLVMessage.h
 * \date Mar 29, 2010
 * \author samael
 */

#ifndef TLVMESSAGE_H_
#define TLVMESSAGE_H_

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
	static const unsigned short TLVType;
	/**
	 * Enumeration of commands. To ensure the size and value of commands, we
	 * use constant unsigned short instead of C++ 'enum' here.
	 */
	static const char *CommandString[];
	static const unsigned short EMPTY;
	static const unsigned short HELLO_MASTER;
	static const unsigned short HELLO_SLAVE;
	static const unsigned short LOAD_ACTOR;
	static const unsigned short RUN_ACTOR;
	static const unsigned short SHUTDOWN;

	TLVMessage(unsigned short c = EMPTY, ITLVObject *param = NULL):
		_cmd(c), _param(param) {}
	inline unsigned short command() const { return _cmd; }
	inline ITLVObject* parameter() const { return _param; }
	inline void setCommand(unsigned short c) { _cmd = c; }
	inline void setParameter(ITLVObject *param) { _param = param; }
	cml::StandardTLVBlock* toTLVBlock() const;

private:
	unsigned short _cmd;
	ITLVObject *_param;
};

}

#endif /* TLVMESSAGE_H_ */
