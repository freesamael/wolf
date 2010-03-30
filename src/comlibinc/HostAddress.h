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
 * @class IPv4 address representation.
 */
class HostAddress
{
public:
	HostAddress(): _addr(INADDR_NONE) {}
	HostAddress(in_addr_t addr): _addr(addr) {}
	HostAddress(const char *addr): _addr(inet_addr(addr)) {}
	HostAddress(const std::string &addr): _addr(inet_addr(addr.c_str())) {}

	inline bool isValid() const { return (_addr != INADDR_NONE); }
	inline in_addr_t toInetAddr() const { return _addr; }
	std::string toString() const;

private:
	in_addr_t _addr;
};

}

#endif /* HOSTADDRESS_H_ */
