#ifndef PRESSURE_H
#define PRESSURE_H

#include "fundamental_types.h"
#include <array>

namespace sensors {

class pressure
{
public:
	pressure();
	~pressure();

	f32 read();

private:
    void init_dig();
    void init_settings();

	i32 fd;
	std::array<i32, 4> dig_t;
	std::array<i32, 10> dig_p;
};

} // namespace sensors

#endif
