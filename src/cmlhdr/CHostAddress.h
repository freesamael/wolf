/**
 * \file CHostAddress.h
 * \date Mar 8, 2010
 * \author samael
 */

#ifndef CHOSTADDRESS_H_
#define CHOSTADDRESS_H_

#include <string>
#include <arpa/inet.h>
#include <sys/types.h>

/// INADDR_NONE is not part of POSIX.
#ifndef INADDR_NONE
#define	INADDR_NONE		((in_addr_t) 0xffffffff)
#endif

namespace cml
{

/**
 * IPv4 address representation.
 */
class CHostAddress
{
public:
	static const CHostAddress LocalhostAddress; ///< Loopback address.
	static const CHostAddress BroadcastAddress; ///< Broadcast address.

	CHostAddress(): _addr(INADDR_NONE) {}
	CHostAddress(in_addr_t addr): _addr(addr) {}
	CHostAddress(const char *addr): _addr(inet_addr(addr)) {}
	CHostAddress(const std::string &addr): _addr(inet_addr(addr.c_str())) {}

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

#endif /* CHOSTADDRESS_H_ */
