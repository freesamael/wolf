/*
 * SharedMemory.h
 *
 *  Created on: Mar 18, 2010
 *      Author: samael
 */

#ifndef SHAREDMEMORY_H_
#define SHAREDMEMORY_H_

#include <string>
#include <d2mce/d2mce.h>

namespace cml
{

class SharedMemory
{
public:
	SharedMemory(std::string name, size_t size);
	~SharedMemory();
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

private:
	const std::string _name;
	d2mce_mutex_t _mutex;
	char *_buf;
	size_t _size;
};

}

#endif /* SHAREDMEMORY_H_ */
