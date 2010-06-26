/**
 * \file Time.cpp
 * \date Jun 26, 2010
 * \author samael
 */

#include <sstream>
#include "Time.h"

using namespace std;

namespace cml
{

Time Time::operator+(const Time &o)
{
	timeval t;
	timeradd(&_t, &o._t, &t);
	return t;
}

Time Time::operator-(const Time &o)
{
	timeval t;
	timersub(&_t, &o._t, &t);
	return t;
}

string Time::toString() const
{
	stringstream s;
	s << _t.tv_sec << "." << _t.tv_usec << " seconds";
	return s.str();
}

}

std::ostream& operator<<(std::ostream &o, const cml::Time &t)
{
	return (o << t.toString());
}
