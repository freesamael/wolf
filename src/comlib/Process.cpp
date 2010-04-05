/*
 * Process.cpp
 *
 *  Created on: Mar 12, 2010
 *      Author: samael
 */

#include <cstdio>
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
	const char **argv = constructArgs(program, argtoks);

	// Execute.
	if ((_proc = fork()) == 0) {
		/* POSIX manpage says it won't modify either the array nor the string,
		 * and the type (char * const *) is used only for compatibility reason.
		 * Hence it's safe to force convert the type here.
		 */
		if (_env.isEmpty())
			execvp(program.c_str(), (char * const *)argv);
		else
			execve(program.c_str(), (char * const *)argv,
					_env.toNullTerminatedArray());
		perror("Process::start()");
	}

	delete argv;
}

/**
 * Construct arguments in char** form used in execve().
 *
 * \note
 * The lifetime of return string arrays depends on input parameters because it
 * uses string.c_str(). Be careful about the lifetime issue and don't call this
 * function by constant c-string such as constructArgs("program_name", ...).
 */
const char** Process::constructArgs(const std::string &program,
		const vector<string> &args)
{
	// + program and NULL.
	const char **argv = new const char * [args.size() + 2];

	// Fill arguments.
	argv[0] = program.c_str();
	for (int i = 1; i <= (int)args.size(); i++)
		argv[i] = args[i - 1].c_str();
	argv[args.size() + 1] = NULL;

	return argv;
}

}
