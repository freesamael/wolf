/*
 * main.cpp
 *
 *  Created on: Mar 6, 2010
 *      Author: samael
 */

#include <cppunit/TextTestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

using namespace CppUnit;

int main(int argc, char *argv[])
{
	TextTestRunner runner;
	runner.addTest(TestFactoryRegistry::getRegistry().makeTest());
	runner.run();
	return 0;
}
