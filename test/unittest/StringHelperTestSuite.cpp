/*
 * StringHelperTestSuite.cpp
 *
 *  Created on: Mar 6, 2010
 *      Author: samael
 */

#include <string>
#include <vector>
#include "StringHelperTestSuite.h"
#include "StringHelper.h"

using namespace std;
using namespace cml;

CPPUNIT_TEST_SUITE_REGISTRATION(StringHelperTestSuite);

void StringHelperTestSuite::testTokenSingleCharDelim()
{
	string str = "192.168.1.254";
	vector<string> tok;
	StringHelper::tokens(str, ".", &tok);

	CPPUNIT_ASSERT_EQUAL(4, (int)tok.size());
	CPPUNIT_ASSERT_EQUAL((string)"192", tok[0]);
	CPPUNIT_ASSERT_EQUAL((string)"168", tok[1]);
	CPPUNIT_ASSERT_EQUAL((string)"1", tok[2]);
	CPPUNIT_ASSERT_EQUAL((string)"254", tok[3]);
}

void StringHelperTestSuite::testTokenMultCharDelim()
{
	string str = "i++ + ++i + --i + i--";
	vector<string> tok;
	StringHelper::tokens(str, " i", &tok);

	CPPUNIT_ASSERT_EQUAL(7, (int)tok.size());
	CPPUNIT_ASSERT_EQUAL((string)"++", tok[0]);
	CPPUNIT_ASSERT_EQUAL((string)"+", tok[1]);
	CPPUNIT_ASSERT_EQUAL((string)"++", tok[2]);
	CPPUNIT_ASSERT_EQUAL((string)"+", tok[3]);
	CPPUNIT_ASSERT_EQUAL((string)"--", tok[4]);
	CPPUNIT_ASSERT_EQUAL((string)"+", tok[5]);
	CPPUNIT_ASSERT_EQUAL((string)"--", tok[6]);
}

void StringHelperTestSuite::testTokenWithOldData()
{
	vector<string> tok;
	tok.push_back("Hello");
	tok.push_back("World");

	string str = "i have a dream, that one day i can graduate.";
	StringHelper::tokens(str, ",.", &tok);

	CPPUNIT_ASSERT_EQUAL(2, (int)tok.size());
	CPPUNIT_ASSERT_EQUAL((string)"i have a dream", tok[0]);
	CPPUNIT_ASSERT_EQUAL((string)" that one day i can graduate", tok[1]);
}
