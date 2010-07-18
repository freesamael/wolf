/**
 * \file MansetFinalizer.h
 * \date Jul 18, 2010
 * \author samael
 */

#ifndef MANSETFINALIZER_H_
#define MANSETFINALIZER_H_

#include <inttypes.h>
#include <AActor.h>

class MansetFinalizer: public wfe::AActor
{
public:
	MansetFinalizer(uint32_t imgwidth, uint32_t imgheight, uint32_t rows);
	~MansetFinalizer();
	void prefire();
	void fire();
	void postfire();
	State state();

private:
	State _state;
	uint32_t _imgwidth, _imgheight, _rows;
	unsigned _nports;
	uint8_t **_imgdata;
};

#endif /* MANSETFINALIZER_H_ */
