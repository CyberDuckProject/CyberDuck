#ifndef DIGITAL_PIN_H
#define DIGITAL_PIN_H

#include "FundamentalTypes.h"
#include <string>

class digital_pin
{
public:
	explicit digital_pin(u32 number);

	bool value() const;
	void set_value(bool value);

private:
	std::string value_path;
};

#endif
