/**
 * \file ProcessTestSuite.cpp
 * \date Mar 13, 2010
 * \author samael
 */

#include <cstdlib>
#include "ProcessTestSuite.h"
#include "CProcess.h"
#include "CStringHelper.h"

using namespace std;
using namespace cml;

CPPUNIT_TEST_SUITE_REGISTRATION(ProcessTestSuite);

void ProcessTestSuite::testConstructArgs()
{
	string prog("program"), str("-arg1 -arg2 -arg3 -arg4 -arg5");
	vector<string> args;
	CStringHelper::tokens(str, " ", &args);

	char **argv = CProcess::constructArgs(prog, args);

	CPPUNIT_ASSERT_EQUAL((string)"program", (string)argv[0]);
	CPPUNIT_ASSERT_EQUAL((string)"-arg1", (string)argv[1]);
	CPPUNIT_ASSERT_EQUAL((string)"-arg2", (string)argv[2]);
	CPPUNIT_ASSERT_EQUAL((string)"-arg3", (string)argv[3]);
	CPPUNIT_ASSERT_EQUAL((string)"-arg4", (string)argv[4]);
	CPPUNIT_ASSERT_EQUAL((string)"-arg5", (string)argv[5]);
	CPPUNIT_ASSERT_EQUAL((char *)NULL, argv[6]);

	for (int i = 0; i <= (int)args.size(); i++)
		free(argv[i]);
	delete [] argv;
}
