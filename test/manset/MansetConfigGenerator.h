/**
 * \file MansetConfigGenerator.h
 * \date Jul 18, 2010
 * \author samael
 */

#ifndef MANSETCONFIGGENERATOR_H_
#define MANSETCONFIGGENERATOR_H_

#include <inttypes.h>
#include <AActor.h>

class MansetConfigGenerator: public wfe::AActor
{
public:
	MansetConfigGenerator(uint32_t imgwidth, uint32_t imgheight, uint32_t rows);
	~MansetConfigGenerator();
	void fire();
	State state() { return _state; }

private:
	State _state;
	uint32_t _imgwidth, _imgheight, _rows;
	unsigned _nports;
};

#endif /* MANSETCONFIGGENERATOR_H_ */
