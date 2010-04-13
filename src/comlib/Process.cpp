/**
 * \file Process.cpp
 * \date Mar 12, 2010
 * \author samael
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <errno.h>
#include "Process.h"
#include "StringHelper.h"

using namespace std;

namespace cml
{

/**
 * Execute a program with given arguments.
 *
 * \note
 * If no environment was specified, it uses evexvp(), which means it searches
 * $PATH for executables. Otherwise it uses execve().
 */
void Process::start(const string &program, const string &args)
{
	// Construct argument list.
	vector<string> argtoks;
	StringHelper::tokens(args, " ", &argtoks);
	char **argv = constructArgs(program, argtoks);

	// Execute.
	if ((_proc = fork()) == 0) {
		/* POSIX manpage says it won't modify either the array nor the string,
		 * and the type (char * const *) is used only for compatibility reason.
		 * Hence it's safe to force convert the type here.
		 */
		if (_env.isEmpty())
			execvp(program.c_str(), argv);
		else
			execve(program.c_str(), argv,
					_env.toNullTerminatedArray());
		perror("Process::start()");
	}

	// Cleanup duplicated data.
	for (int i = 0; i <= (int)args.size(); i++)
		free(argv[i]);
	delete [] argv;
}

/**
 * Construct arguments in char** form used in execve().
 *
 * \note
 * Remember to free the array (by delete) and the elements inside the array (by
 * free() because strdup uses malloc()).
 */
char** Process::constructArgs(const std::string &program,
		const vector<string> &args)
{
	// + program and NULL.
	char **argv = new char *[args.size() + 2];

	// Fill arguments.
	argv[0] = strdup(program.c_str());
	for (int i = 1; i <= (int)args.size(); i++)
		argv[i] = strdup(args[i - 1].c_str());
	argv[args.size() + 1] = NULL;

	return argv;
}

}
