/*
 * TLVStringCreator.cpp
 *
 *  Created on: Mar 11, 2010
 *      Author: samael
 */

#include <cstring>
#include "TLVStringCreator.h"
#include "ITLVObject.h"
#include "TLVBlock.h"

using namespace std;

namespace cml
{

ITLVObject* TLVStringCreator::create(const ITLVBlock &blk) const
{
	// Convert to null-terminated string.
	char *ntstr = new char[blk.length() + 1];
	strncpy(ntstr, blk.value(), blk.length());
	ntstr[blk.length()] = '\0';

	// Initialize TLVString.
	TLVString *str = new TLVString(ntstr);

	// Cleanup
	delete [] ntstr;

	return str;
}

}
