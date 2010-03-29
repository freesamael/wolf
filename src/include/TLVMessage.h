/*
 * TLVMessage.h
 *
 *  Created on: Mar 29, 2010
 *      Author: samael
 */

#ifndef TLVMESSAGE_H_
#define TLVMESSAGE_H_

#include "ITLVObject.h"

namespace wfe
{

class TLVMessage: cml::ITLVObject
{
public:
	typedef enum Command {
		INVALID,
		ADD_MASTER,
		ADD_SLAVE,
		RUN_ACTOR
	} Command;
	TLVMessage(Command c = INVALID, ITLVObject *param = NULL):
		_cmd(c), _param(NULL) {}
	void run();
	inline Command command() const { return _cmd; }
	inline ITLVObject* parameter() const { return _param; }
	inline void setCommand(Command c) { _cmd = c; }
	inline void setParameter(ITLVObject *param) { _param = param; }
	cml::TLVBlock* toTLVBlock() const;
private:
	Command _cmd;
	ITLVObject *_param;
};

}

#endif /* TLVMESSAGE_H_ */
