/**
 * \file TLVArray.h
 * \date Apr 8, 2010
 * \author samael
 */

#ifndef TLVARRAY_H_
#define TLVARRAY_H_

#include <vector>
#include "ITLVObject.h"

namespace cml
{

/**
 * A container to encapsulate TLV objects. It uses std::vector as the underlying
 * container. TLVArray does NOT take the ownership of elements, which means it
 * won't delete/free the memory blocks of elements. If the elements are created
 * on dynamic memory, the user needs to maintain the memory to avoid memory
 * leaks.
 */
class TLVArray: public ITLVObject
{
public:
	TLVArray(): _elem() {}
	void addElement(ITLVObject *obj) { _elem.push_back(obj); }
	std::vector<ITLVObject *>& elements() { return _elem; }
	StandardTLVBlock* toTLVBlock() const;

private:
	std::vector<ITLVObject *> _elem;
};

}

#endif /* TLVARRAY_H_ */
