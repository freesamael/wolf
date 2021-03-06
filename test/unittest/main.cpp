/**
 * \file main.cpp
 * \date Mar 6, 2010
 * \author samael
 */

#include <cppunit/TextTestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

using namespace CppUnit;

int main()
{
	TextTestRunner runner;
	runner.addTest(TestFactoryRegistry::getRegistry().makeTest());
	runner.run();
	return 0;
}
