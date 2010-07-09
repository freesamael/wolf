/**
 * \file CSharedMemory.h
 * \date Mar 18, 2010
 * \author samael
 */

#ifndef CSHAREDMEMORY_H_
#define CSHAREDMEMORY_H_

#include <string>
#include "HelperMacros.h"
#include "IDrop.h"

namespace wfe
{

#ifdef ENABLE_D2MCE /* DSM mode */

#include <d2mce/d2mce.h>
/**
 * SharedMemory represents a piece of shared memory on D2MCE tuple space. A
 * SharedMemory should be constructed by D2MCE::createSharedMemory().
 */
class SharedMemory: public IDrop
{
public:
	SharedMemory(const std::string &name, char *buf, size_t size,
		d2mce_mutex_t *mutex):
		_name(name), _buf(buf), _size(size), _mutex(mutex) {}
	inline const std::string& name() const { return _name; }
	inline size_t size() const { return _size; }
	inline char* buffer() { return _buf; }
	inline bool lock() { return (d2mce_mutex_lock(_mutex) == 1); }
	inline bool unlock() { return (d2mce_mutex_unlock(_mutex) == 1); }
	inline bool load() { return (d2mce_load(_buf) == 1); }
	inline bool store() { return (d2mce_store(_buf) == 1); }
	inline bool mload(unsigned int offset, unsigned int length) {
		return (d2mce_mload(_buf, offset, length) == 1); }
	inline bool mstore(unsigned int offset, unsigned int length) {
		return (d2mce_mstore(_buf, offset, length) == 1); }
	IDrop* clone() const;

private:
	SharedMemory(const SharedMemory &UNUSED(o)):
		_name(), _buf(NULL), _size(0), _mutex(NULL) {}
	SharedMemory& operator=(const SharedMemory &UNUSED(o)) { return *this; }
	std::string _name;
	char *_buf;
	size_t _size;
	d2mce_mutex_t *_mutex;
};

#endif /* ENABLE_D2MCE */

}

#endif /* CSHAREDMEMORY_H_ */
