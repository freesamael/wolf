/**
 * \file CProcessEnvironment.h
 * \date Mar 12, 2010
 * \author samael
 */

#ifndef CPROCESSENVIRONMENT_H_
#define CPROCESSENVIRONMENT_H_

#include <map>
#include <string>

namespace cml
{

/**
 * Environment variables for CProcess.
 */
class CProcessEnvironment
{
public:
	CProcessEnvironment(): _envmap() {}
	CProcessEnvironment(const CProcessEnvironment &env):
		_envmap(env._envmap) {}
	inline bool isEmpty() const { return _envmap.empty(); }
	void setVariable(const std::string &variable, const std::string &value);
	void clearVariable(const std::string &variable);
	std::string lookupValue(const std::string &variable) const;
	char** toNullTerminatedArray() const;

	static void freeNullTerminatedArray(char **array);
	static CProcessEnvironment systemEnvironment();

private:
	std::map<std::string, std::string> _envmap;
};

}

#endif /* CPROCESSENVIRONMENT_H_ */
