/**
 * \file CProcess.h
 * \date Mar 12, 2010
 * \author samael
 */

#ifndef PROCESS_H_
#define PROCESS_H_

#include <string>
#include <vector>
#include <unistd.h>
#include "CProcessEnvironment.h"

namespace wolf
{

/**
 * Used to execute an external process with given environment variables.
 *
 * \see CProcessEnvironment
 */
class CProcess
{
public:
	CProcess(): _proc(0), _env() {}
	void setProcessEnvironment(const CProcessEnvironment &env) { _env = env; }
	inline CProcessEnvironment processEnvironment() const { return _env; }
	void start(const std::string &program, const std::string &args = "");
	static char** constructArgs(const std::string &program,
				const std::vector<std::string> &args);

private:
	pid_t _proc;
	CProcessEnvironment _env;
};

}

#endif /* CPROCESS_H_ */
