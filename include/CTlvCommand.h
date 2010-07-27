/**
 * \file CTlvCommand.h
 * \date Mar 29, 2010
 * \author samael
 */

#ifndef CTLVCOMMAND_H_
#define CTLVCOMMAND_H_

#include <string>
#include <vector>
#include <stdint.h>
#include "ITlvObject.h"

namespace wolf
{

/**
 * TLVCommand represents the command used for communications between runners
 * and master. It doesn't take the ownership of parameters unless autoclean is
 * set to true (by default it's false), so users need to delete the parameters
 * if it's allocated on heap, or set autoclean property.
 */
class CTlvCommand: public wolf::ITlvObject
{
public:
	typedef enum Command {
		EMPTY = 0,			///< Empty command.
		SHUTDOWN,			///< Shutdown the runner.
		HELLO_MASTER,		///< Hello message from the master node.
		HELLO_RUNNER,		///< Hello message from a runner.
		WORKER_RUN,			///< Send an worker to a runner and run it.
		WORKER_STEAL,		///< Ask for stealing a worker.
		WORKER_STEAL_FAILED,///< Ack that no worker to steal.
		WORKER_FINISHED,	///< Send an finished worker back.
		RUNNER_ADD,			///< Ask a runner to connect to another runner.
		RUNNER_START		/**< Tell the runner to start working, which also \
							     indicates the runner stop waiting for \
							     connections from other runners. */
	} Command;
	static const std::string CommandString[];

	CTlvCommand(Command c = EMPTY, bool ac = false): _cmd(c), _params(),
			_autoclean(ac) {}
	virtual ~CTlvCommand();
	inline bool autoclean() const { return _autoclean; }
	inline void setAutoclean(bool ac) { _autoclean = ac; }
	inline Command command() const { return _cmd; }
	inline void setCommand(Command c) { _cmd = c; }
	inline const std::vector<wolf::ITlvObject *> parameters() const
			{ return _params; }
	inline void addParameter(ITlvObject *obj) { _params.push_back(obj); }
	virtual wolf::CTlvBlock* toTLVBlock() const;

private:
	Command _cmd;
	std::vector<wolf::ITlvObject *> _params;
	bool _autoclean;
};

}

#endif /* CTLVCOMMAND_H_ */
