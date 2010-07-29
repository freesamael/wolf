/**
 * \file XWolf.h
 * \date Jul 27, 2010
 * \author samael
 */

#ifndef XWOLF_H_
#define XWOLF_H_

#include <exception>
#include <string>

namespace wolf
{

/**
 * XWolf represents all wolf exceptions.
 */
class XWolf: public std::exception
{
public:
	explicit XWolf(const std::string &remark = "") throw();
	virtual ~XWolf() throw() {}
	inline virtual const char* what() const throw() { return _estr.c_str(); }
	inline virtual const std::string& toString() const throw() { return _estr; }

private:
	std::string _estr;
};

}

#endif /* XWOLF_H_ */
