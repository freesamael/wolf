/**
 * \file CTime.cpp
 * \date Jun 26, 2010
 * \author samael
 */

#include "CTime.h"
#include <sstream>

using namespace std;

namespace wolf
{

CTime CTime::operator+(const CTime &o)
{
	timeval t;
	timeradd(&_t, &o._t, &t);
	return t;
}

CTime CTime::operator-(const CTime &o)
{
	timeval t;
	timersub(&_t, &o._t, &t);
	return t;
}

timespec CTime::toTimespec() const
{
	timespec t;
	t.tv_sec = _t.tv_sec;
	t.tv_nsec = _t.tv_usec * 1000;
	return t;
}

string CTime::toString() const
{
	stringstream s;
	s << (unsigned)_t.tv_sec << "." << (unsigned)_t.tv_usec << " seconds";
	return s.str();
}

}

std::ostream& operator<<(std::ostream &o, const wolf::CTime &t)
{
	return (o << t.toString());
}
