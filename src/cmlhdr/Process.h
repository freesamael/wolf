/**
 * \file Process.h
 * \date Mar 12, 2010
 * \author samael
 */

#ifndef PROCESS_H_
#define PROCESS_H_

#include <string>
#include <vector>
#include <unistd.h>
#include "ProcessEnvironment.h"

namespace cml
{

/**
 * Used to execute an external process with given environment variables.
 *
 * \see ProcessEnvironment
 */
class Process
{
public:
	Process(): _proc(0) {}
	void setProcessEnvironment(const ProcessEnvironment &env) { _env = env; }
	inline ProcessEnvironment processEnvironment() const { return _env; }
	void start(const std::string &program, const std::string &args = "");
	static char** constructArgs(const std::string &program,
				const std::vector<std::string> &args);

private:
	pid_t _proc;
	ProcessEnvironment _env;
};

}

#endif /* PROCESS_H_ */
