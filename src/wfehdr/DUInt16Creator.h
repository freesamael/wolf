/**
 * \file DUInt16Creator.h
 * \date Jun 20, 2010
 * \author samael
 */

#ifndef DUINT16CREATOR_H_
#define DUINT16CREATOR_H_

#include "TLVUInt16Creator.h"
#include "DUInt16.h"

namespace wfe
{

/**
 * Creator for DUInt16.
 */
class DUInt16Creator: public cml::TLVUInt16Creator
{
public:
	cml::ITLVObject* create() const { return new DUInt16(); }
	cml::ITLVObject* create(const cml::ITLVBlock &blk) const;
};

}

#endif /* DUINT16CREATOR_H_ */
