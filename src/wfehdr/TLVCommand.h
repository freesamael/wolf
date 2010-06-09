/**
 * \file TLVCommand.h
 * \date Mar 29, 2010
 * \author samael
 */

#ifndef TLVCOMMAND_H_
#define TLVCOMMAND_H_

#include <string>
#include <vector>
#include <stdint.h>
#include "ITLVObject.h"

namespace wfe
{

/**
 * TLVCommand represents the command used for communications between runners
 * and master. It doesn't take the ownership of parameters unless autoclean is
 * set to true (by default it's false), so users need to delete the parameters
 * if it's allocated on heap, or set autoclean property.
 */
class TLVCommand: public cml::ITLVObject
{
public:
	/**
	 * Enumeration of commands. To ensure the size and value of commands, we
	 * use constant uint16_t instead of C++ 'enum' here.
	 */
	static const std::string CommandString[];
	static const uint16_t EMPTY;
	static const uint16_t SHUTDOWN;
	static const uint16_t HELLO_MASTER;
	static const uint16_t HELLO_RUNNER;
	static const uint16_t WORKER_RUN;
	static const uint16_t WORKER_FINISHED;
	static const uint16_t RUNNER_ADD;
	static const uint16_t RUNNER_START;

	TLVCommand(uint16_t c = EMPTY, bool ac = false): _cmd(c), _params(),
			_autoclean(ac) {}
	virtual ~TLVCommand();
	inline bool autoclean() const { return _autoclean; }
	inline void setAutoclean(bool ac) { _autoclean = ac; }
	inline uint16_t command() const { return _cmd; }
	inline void setCommand(uint16_t c) { _cmd = c; }
	inline const std::vector<cml::ITLVObject *> parameters() const
			{ return _params; }
	inline void addParameter(ITLVObject *obj) { _params.push_back(obj); }
	virtual cml::StandardTLVBlock* toTLVBlock() const;

private:
	uint16_t _cmd;
	std::vector<cml::ITLVObject *> _params;
	bool _autoclean;
};

}

#endif /* TLVCOMMAND_H_ */
