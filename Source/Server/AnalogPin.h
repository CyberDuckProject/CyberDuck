#ifndef ANALOG_PIN_H
#define ANALOG_PIN_H

#include "FundamentalTypes.h"
#include <string>

class analog_pin
{
public:
	explicit analog_pin(u32 number);

	u32 millivolts() const;
	f32 volts() const;

private:
	std::string path;
};

#endif
