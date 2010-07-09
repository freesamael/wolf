/**
 * \file CTlvArray.h
 * \date Apr 8, 2010
 * \author samael
 */

#ifndef CTLVARRAY_H_
#define CTLVARRAY_H_

#include <vector>
#include "ITlvObject.h"

namespace cml
{

/**
 * A container to encapsulate TLV objects. It uses std::vector as the underlying
 * container. TLVArray does NOT take the ownership of elements, which means it
 * won't delete/free the memory blocks of elements. If the elements are created
 * on dynamic memory, the user needs to maintain the memory to avoid memory
 * leaks.
 */
class CTlvArray: public ITlvObject
{
public:
	CTlvArray(): _elem() {}
	void addElement(ITlvObject *obj) { _elem.push_back(obj); }
	std::vector<ITlvObject *>& elements() { return _elem; }
	CTlvBlock* toTLVBlock() const;

private:
	std::vector<ITlvObject *> _elem;
};

}

#endif /* CTLVARRAY_H_ */
