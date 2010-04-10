/*
 * Runner.h
 *
 *  Created on: Apr 1, 2010
 *      Author: samael
 */

#ifndef RUNNER_H_
#define RUNNER_H_

#include <string>

namespace wfe
{

class Runner
{
public:
	void run(unsigned short runner_port, unsigned short master_port, const
			std::string &appname);

};

}

#endif /* RUNNER_H_ */
