/**
 * \file testtlv.h
 * \date Jul 15, 2010
 * \author samael
 */

#ifndef TESTTLV_H_
#define TESTTLV_H_

#include <CTlvString.h>

cml::CTlvString generateString(char c, unsigned bytecount)
{
	char *str = new char[bytecount];
	for (unsigned i = 0; i < bytecount - 1; i++)
		str[i] = c;
	str[bytecount - 1] = '\0';

	cml::CTlvString cstr(str);
	delete [] str;
	return cstr;
}


#endif /* TESTTLV_H_ */
