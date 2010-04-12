#ifndef TLVSHAREDMEMORYINFO_H_
#define TLVSHAREDMEMORYINFO_H_

#include <string>
#include <ITLVObject.h>

namespace wfe
{

/**
 * A simple structure to hold the name and size of shared memory in order to
 * make worker actors being able to allocate shared memory after migrated to
 * remote hosts.
 */
class TLVSharedMemoryInfo: public cml::ITLVObject
{
public:
	TLVSharedMemoryInfo(): _size(0) {}
	TLVSharedMemoryInfo(const std::string &name, size_t size):
		_name(name), _size(size) {}
	inline const std::string& name() const { return _name; }
	inline size_t size() const { return _size; }
	inline void setName(std::string &name) { _name = name; }
	inline void setSize(size_t size) { _size = size; }
	cml::StandardTLVBlock* toTLVBlock() const;

private:
	std::string _name;
	size_t _size;
};

}

#endif /* TLVSHAREDMEMORYINFO_H_ */
