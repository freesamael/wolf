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
	XWolf() throw();
	virtual ~XWolf() throw();
};

}

#endif /* XWOLF_H_ */