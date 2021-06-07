#ifndef SENSORS_H
#define SENSORS_H

#include "fundamental_types.h"

namespace sensors {

void init();

f32 water_temperature();
f32 water_turbidity();
f32 atmospheric_dust();

} // namespace sensors

#endif
