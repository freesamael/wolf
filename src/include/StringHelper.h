/*
 * StringHelper.h
 *
 *  Created on: Mar 6, 2010
 *      Author: samael
 */

#ifndef STRINGHELPER_H_
#define STRINGHELPER_H_

#include <vector>
#include <string>

namespace cml
{

class StringHelper
{
public:
	static void tokens(const std::string &str, const std::string &delim,
			std::vector<std::string> *out_vector);
	static size_t strlcpy(char *dst, const char *src, size_t siz);
	static size_t strlcat(char *dst, const char *src, size_t siz);
};

}

#endif /* STRINGHELPER_H_ */
