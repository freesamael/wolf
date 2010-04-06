/*
 * HostAddress.h
 *
 *  Created on: Mar 8, 2010
 *      Author: samael
 */

#ifndef HOSTADDRESS_H_
#define HOSTADDRESS_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>

namespace cml
{

/**
 * IPv4 address representation.
 */
class HostAddress
{
public:
	static const HostAddress LocalhostAddress;
	static const HostAddress BroadcastAddress;

	HostAddress(): _addr(INADDR_NONE) {}
	HostAddress(in_addr_t addr): _addr(addr) {}
	HostAddress(const char *addr): _addr(inet_addr(addr)) {}
	HostAddress(const std::string &addr): _addr(inet_addr(addr.c_str())) {}

	inline bool isValid() const { return (_addr != INADDR_NONE); }
	inline in_addr_t toInetAddr() const { return _addr; }
	std::string toString() const;

	inline void setAddr(in_addr_t addr) { _addr = addr; }
	inline void setAddr(const char *addr) { _addr = inet_addr(addr); }
	inline void setAddr(const std::string &addr) { setAddr(addr.c_str()); }

private:
	in_addr_t _addr;
};

}

#endif /* HOSTADDRESS_H_ */
