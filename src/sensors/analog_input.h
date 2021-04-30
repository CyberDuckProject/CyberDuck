#ifndef ANALOG_INPUT_H
#define ANALOG_INPUT_H

#include "fundamental_types.h"

namespace sensors {

f32 analog_pin(u32 number);
f32 before_voltage_divider(f32 voltage);

} // namespace sensors

#endif
