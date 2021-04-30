#include "dust.h"

#include "analog_input.h"
#include <stdexcept>
#include <unistd.h>

namespace sensors {

dust::dust() : chip{"gpiochip3"}
{
	gpiod::line_request config{};
	config.request_type = gpiod::line_request::DIRECTION_OUTPUT;
	config.consumer = "Consumer";

	line = chip.get_line(1);
	line.request(config);
	line.set_value(0);
}

f32 dust::read()
{
	f32 result{};
	for (u32 i = 0; i < 10 && result <= 0.f; ++i)
	{
		line.set_value(1);
		usleep(280);
		f32 voltage = analog_pin(3);
		line.set_value(0);

		result = (before_voltage_divider(voltage) - 0.6f) * 0.2f;

		usleep(10000);
	}

	if (result <= 0.f)
	{
		throw std::runtime_error{"dust sensor measured no dust 10 times"};
		return 0.f;
	}

	return result;
}

} // namespace sensors
