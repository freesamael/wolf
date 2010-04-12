#ifndef IITERATIVEACTOR_H_
#define IITERATIVEACTOR_H_

#include "IActor.h"

namespace wfe
{

/**
 * \note
 * Scheduler should continuously call fire() until firecond() is false.
 */
class IIterativeActor: public IActor
{
public:
	virtual ~IIterativeActor() {}
	virtual bool firecond() const = 0;
};

}

#endif /* IITERATIVEACTOR_H_ */
