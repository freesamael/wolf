/*
 * ProcessEnvironment.h
 *
 *  Created on: Mar 12, 2010
 *      Author: samael
 */

#ifndef PROCESSENVIRONMENT_H_
#define PROCESSENVIRONMENT_H_

#include <map>
#include <string>

namespace cml
{

class ProcessEnvironment
{
public:
	ProcessEnvironment() {}
	ProcessEnvironment(const ProcessEnvironment &env):
		_envmap(env._envmap) {}
	inline bool isEmpty() const { return _envmap.empty(); }
	void setVariable(const std::string &variable, const std::string &value);
	void clearVariable(const std::string &variable);
	std::string lookupValue(const std::string &variable) const;
	char** toNullTerminatedArray() const;

	static void freeNullTerminatedArray(char **array);
	static ProcessEnvironment systemEnvironment();

private:
	std::map<std::string, std::string> _envmap;
};

}

#endif /* PROCESSENVIRONMENT_H_ */
