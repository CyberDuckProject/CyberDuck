#ifndef DUST_H
#define DUST_H

#include "fundamental_types.h"
#include <gpiod.hpp>

namespace sensors {

class dust
{
public:
	dust();

	f32 read();

private:
	gpiod::chip chip;
	gpiod::line line;
};

} // namespace sensors

#endif
