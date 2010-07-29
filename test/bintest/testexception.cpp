/**
 * \file testexception.cpp
 * \date Jul 28, 2010
 * \author samael
 */

#include <XWolf.h>

using namespace wolf;

class FooBar
{
public:
	void foo() { bar(); }
	void bar() { throw XWolf("test exception throwing."); }
};

int main()
{
	FooBar fb;
	fb.foo();
	return 0;
}
