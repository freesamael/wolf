/**
 * \file ProcessEnvironment.cpp
 * \date Mar 12, 2010
 * \author samael
 */

#include <cstring>
#include <unistd.h>
#include "StringHelper.h"
#include "ProcessEnvironment.h"

extern char **environ;

using namespace std;

namespace cml
{

/**
 * Set a variable with given value. It overwrites old one if any.
 */
void ProcessEnvironment::setVariable(const string &variable,
		const string &value)
{
	map<string, string>::iterator iter;
	if ((iter = _envmap.find(variable)) != _envmap.end())
		_envmap.erase(iter);
	_envmap[variable] = value;
}

/**
 * Clear (delete) a variable. If the variable does not exist, it takes no
 * effect.
 */
void ProcessEnvironment::clearVariable(const string &variable)
{
	map<string, string>::iterator iter;
	if ((iter = _envmap.find(variable)) != _envmap.end())
		_envmap.erase(iter);
}

/**
 * Find the value of given variable. If no such variable exists, it returns an
 * empty string.
 */
string ProcessEnvironment::lookupValue(const string &variable) const
{
	map<string, string>::const_iterator iter;
	if ((iter = _envmap.find(variable)) != _envmap.end())
		return iter->second;
	return string();
}

/**
 * Get the list of variables in null-terminated array form.
 *
 * \return
 * Pointer to the array. User should use freeNullTerminatedArray() to deallocate
 * it.
 *
 * \note
 * This function is NOT thread-safe.
 */
char** ProcessEnvironment::toNullTerminatedArray() const
{
	int size = _envmap.size();
	char **array = new char *[size + 1];
	map<string, string>::const_iterator iter = _envmap.begin();

	// Insert values;
	for (int i = 0; i < size; i++) {
		string str(iter->first + "=" + iter->second);
		array[i] = new char[str.length() + 1];
		StringHelper::strlcpy(array[i], str.c_str(), str.length() + 1);
		iter++;
	}

	// Null-terminated.
	array[size] = NULL;

	return array;
}

/**
 * Deallocate an array came from toNullTerminatedArray().
 */
void ProcessEnvironment::freeNullTerminatedArray(char **array)
{
	// Free elements.
	for (int i = 0; array[i] != NULL; i++)
		delete [] array[i];

	// Free array.
	delete [] array;
}

/**
 * Get the environment variables of current program.
 */
ProcessEnvironment ProcessEnvironment::systemEnvironment()
{
	ProcessEnvironment env;
	for (int i = 0; environ[i] != NULL; i++) {
		// Find the first '=' to split substrings.
		string ent(environ[i]);
		string::size_type nend = ent.find_first_of("=");
		if (nend != string::npos) {
			string::size_type vbegin = ent.find_first_not_of("=", nend);
			if (vbegin != string::npos)
				env.setVariable(ent.substr(0, nend), ent.substr(vbegin));
		}
	}
	return env;
}

}
