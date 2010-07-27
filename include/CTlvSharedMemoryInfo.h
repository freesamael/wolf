/**
 * \file CTlvSharedMemoryInfo.h
 * \date Apr 8, 2010
 * \author samael
 */

#ifndef CTLVSHAREDMEMORYINFO_H_
#define CTLVSHAREDMEMORYINFO_H_

#include <string>
#include "ITlvObject.h"

namespace wolf
{

/**
 * A simple structure to hold the name and size of shared memory in order to
 * make worker actors being able to allocate shared memory after migrated to
 * remote hosts.
 */
class CTlvSharedMemoryInfo: public ITlvObject
{
public:
	CTlvSharedMemoryInfo(): _name(), _size(0) {}
	CTlvSharedMemoryInfo(const std::string &name, size_t size):
		_name(name), _size(size) {}
	inline const std::string& name() const { return _name; }
	inline size_t size() const { return _size; }
	inline void setName(std::string &name) { _name = name; }
	inline void setSize(size_t size) { _size = size; }
	CTlvBlock* toTLVBlock() const;

private:
	std::string _name;
	size_t _size;
};

}

#endif /* CTLVSHAREDMEMORYINFO_H_ */
