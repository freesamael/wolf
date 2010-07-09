/**
 * \file CTime.cpp
 * \date Jun 26, 2010
 * \author samael
 */

#include <sstream>
#include "CTime.h"

using namespace std;

namespace cml
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

string CTime::toString() const
{
	stringstream s;
	s << _t.tv_sec << "." << _t.tv_usec << " seconds";
	return s.str();
}

}

std::ostream& operator<<(std::ostream &o, const cml::CTime &t)
{
	return (o << t.toString());
}
