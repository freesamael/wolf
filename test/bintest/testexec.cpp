/**
 * \file testexec.cpp
 * \date Apr 5, 2010
 * \author samael
 */

#include <string>
#include <CProcess.h>

using namespace std;
using namespace cml;

int main()
{
	CProcess proc;
	string bin = "ls";

	proc.start(bin);
	return 0;
}
