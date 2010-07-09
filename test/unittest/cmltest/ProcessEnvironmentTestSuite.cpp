/**
 * \file ProcessEnvironmentTestSuite.cpp
 * \date Mar 13, 2010
 * \author samael
 */

#include <unistd.h>
#include "ProcessEnvironmentTestSuite.h"
#include "CProcessEnvironment.h"

using namespace std;
using namespace cml;

CPPUNIT_TEST_SUITE_REGISTRATION(ProcessEnvironmentTestSuite);

void ProcessEnvironmentTestSuite::testSystemEnvironment()
{
	CProcessEnvironment env(CProcessEnvironment::systemEnvironment());

	for (int i = 0; environ[i] != NULL; i++) {
		string ent(environ[i]);
		string var(ent.substr(0, ent.find_first_of("=")));

		CPPUNIT_ASSERT_EQUAL(ent, var + "=" + env.lookupValue(var));
	}
}

void ProcessEnvironmentTestSuite::testSetClearVariable()
{
	CProcessEnvironment env;

	env.setVariable("obama", "yes, we can");
	CPPUNIT_ASSERT_EQUAL((string)"yes, we can", env.lookupValue("obama"));

	env.clearVariable("obama");
	CPPUNIT_ASSERT(env.lookupValue("obama").empty());
}
