/*
 * testexec.cpp
 *
 *  Created on: Apr 5, 2010
 *      Author: samael
 */

#include <string>
#include <Process.h>

using namespace std;
using namespace cml;

int main()
{
	Process proc;
	string bin = "ls";

	proc.start(bin);
	return 0;
}
