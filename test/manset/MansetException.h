/**
 * \file MansetException.h
 * \date Jul 17, 2010
 * \author samael
 */

#ifndef MANSETEXCEPTION_H_
#define MANSETEXCEPTION_H_

#include <exception>
#include <string>

class MansetException: public std::exception
{
public:
	MansetException(const std::string &msg) throw(): _msg(msg) {}
	~MansetException() throw() {}
	const char* what() const throw() { return _msg.c_str(); }

private:
	std::string _msg;
};

#endif /* MANSETEXCEPTION_H_ */
