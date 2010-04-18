/**
 * \file SharedMemory.h
 * \date Mar 18, 2010
 * \author samael
 */

#ifndef SHAREDMEMORY_H_
#define SHAREDMEMORY_H_

#include <string>
#include "IDrop.h"

namespace wfe
{

#ifndef DISABLE_D2MCE

#include <d2mce/d2mce.h>
/**
 * SharedMemory represents a piece of shared memory on D2MCE tuple space. A
 * SharedMemory should be constructed by D2MCE::createSharedMemory() and the
 * lifetime is managed by D2MCE.
 */
class SharedMemory: public IDrop
{
public:
	SharedMemory(std::string name, size_t size);
	inline const std::string& name() const { return _name; }
	inline size_t size() const { return _size; }
	inline char* buffer() { return _buf; }
	inline bool lock() { return (d2mce_mutex_lock(&_mutex) == 1); }
	inline bool unlock() { return (d2mce_mutex_unlock(&_mutex) == 1); }
	inline bool load() { return (d2mce_load(_buf) == 1); }
	inline bool store() { return (d2mce_store(_buf) == 1); }
	inline bool mload(unsigned int offset, unsigned int length) {
		return (d2mce_mload(_buf, offset, length) == 1); }
	inline bool mstore(unsigned int offset, unsigned int length) {
		return (d2mce_mstore(_buf, offset, length) == 1); }
	IDrop* clone() const;

private:
	const std::string _name;
	d2mce_mutex_t _mutex;
	char *_buf;
	size_t _size;
};

#else

/**
 * A dummy class used to make compiler happy.
 */
class SharedMemory: public IDrop
{
public:
	SharedMemory(std::string name, size_t size) {}
	inline const std::string& name() const { static std::string s; return s; }
	inline size_t size() const { return 0; }
	inline char* buffer() { return NULL; }
	inline bool lock() { return false; }
	inline bool unlock() { return false; }
	inline bool load() { return false; }
	inline bool store() { return false; }
	inline bool mload(unsigned int offset, unsigned int length) {
		return false; }
	inline bool mstore(unsigned int offset, unsigned int length) {
		return false; }
	IDrop* clone() const { return NULL; }
};

#endif /* DISABLE_D2MCE */

}

#endif /* SHAREDMEMORY_H_ */
