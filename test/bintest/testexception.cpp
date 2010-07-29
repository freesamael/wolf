/**
 * \file testexception.cpp
 * \date Jul 28, 2010
 * \author samael
 */

#include <iostream>
#include <XWolf.h>

using namespace std;
using namespace wolf;

class FooBar
{
public:
	void foo() { bar(); }
	void bar() { throw XWolf("test exception throwing."); }
};

int main()
{
	try {
		FooBar fb;
		fb.foo();
	} catch (XWolf &x) {
		cout << x.toString() << endl;
	}
	return 0;
}
