/**
 * \file CTlvStringCreator.cpp
 * \date Mar 11, 2010
 * \author samael
 */

#include "CTlvStringCreator.h"

#include <cstring>
#include "ITlvObject.h"
#include "CTlvBlock.h"

using namespace std;

namespace wolf
{

ITlvObject* CTlvStringCreator::create(const ITlvBlock &blk) const
{
	// Convert to null-terminated string.
	char *ntstr = new char[blk.length() + 1];
	strncpy(ntstr, blk.value(), blk.length());
	ntstr[blk.length()] = '\0';

	// Initialize TLVString.
	CTlvString *str = new CTlvString(ntstr);

	// Cleanup
	delete [] ntstr;

	return str;
}

}
