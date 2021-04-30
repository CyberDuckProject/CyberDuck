#include "pressure.h"

#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <stdexcept>
#include <sys/ioctl.h>
#include <unistd.h>

namespace sensors {

pressure::pressure()
{
	if ((fd = open("/dev/i2c-2", O_RDWR)) < 0)
	{
		throw std::runtime_error{"cannot open file /dev/i2c-2"};
	}

	if (ioctl(fd, I2C_SLAVE, 0x76) < 0)
	{
		throw std::runtime_error{"cannot set up pressure sensor as i2c slave"};
	}

	init_dig();
	init_settings();
}

pressure::~pressure()
{
    if (fd > 0)
    {
        close(fd);
    }
}

f32 pressure::read()
{
	std::array<u8, 1> reg{0xF7};
	write(fd, reg.data(), reg.size());

	std::array<u8, 8> data{};
	if (::read(fd, data.data(), data.size()) != data.size())
	{
		throw std::runtime_error{"cannot read 8 bytes from register 0xF7 of pressure sensor"};
	}

	u64 adc_p{(((u64)data[0] * 65536) + ((u64)data[1] * 256) + (u64)(data[2] & 0xF0)) / 16};
	u64 adc_t{(((u64)data[3] * 65536) + ((u64)data[4] * 256) + (u64)(data[5] & 0xF0)) / 16};

	f32 var1{(((f32)adc_t) / 16384.f - ((f32)dig_t[1]) / 1024.f) * ((f32)dig_t[2])};
	f32 var2{((((f32)adc_t) / 131072.f - ((f32)dig_t[1]) / 8192.f) *
	          (((f32)adc_t) / 131072.f - ((f32)dig_t[1]) / 8192.f)) *
	         ((f32)dig_t[3])};
	f32 t_fine{var1 + var2};

	var1 = ((f32)t_fine / 2.f) - 64000.f;
	var2 = var1 * var1 * ((f32)dig_p[6]) / 32768.f;
	var2 = var2 + var1 * ((f32)dig_p[5]) * 2.f;
	var2 = (var2 / 4.f) + (((f32)dig_p[4]) * 65536.f);
	var1 = (((f32)dig_p[3]) * var1 * var1 / 524288.f + ((f32)dig_p[2]) * var1) / 524288.f;
	var1 = (1.f + var1 / 32768.f) * ((f32)dig_p[1]);
	f32 p{1048576.f - (f32)adc_p};
	p = (p - (var2 / 4096.f)) * 6250.f / var1;
	var1 = ((f32)dig_p[9]) * p * p / 2147483648.f;
	var2 = p * ((f32)dig_p[8]) / 32768.f;

	return (p + (var1 + var2 + ((f32)dig_p[7])) / 16.f) / 100.f;
}

void pressure::init_dig()
{
	std::array<u8, 1> reg{0x88};
	write(fd, reg.data(), reg.size());

	std::array<u8, 24> data{0};
	if (::read(fd, data.data(), data.size()) != data.size())
	{
		throw std::runtime_error{"cannot read 24 bytes from register 0x88 of pressure sensor"};
	}

	dig_t[1] = data[1] * 256 + data[0];
	dig_t[2] = data[3] * 256 + data[2];
	if (dig_t[2] > 32767)
	{
		dig_t[2] -= 65536;
	}
	dig_t[3] = data[5] * 256 + data[4];
	if (dig_t[3] > 32767)
	{
		dig_t[3] -= 65536;
	}

	dig_p[1] = data[7] * 256 + data[6];
	dig_p[2] = data[9] * 256 + data[8];
	if (dig_p[2] > 32767)
	{
		dig_p[2] -= 65536;
	}

	dig_p[3] = data[11] * 256 + data[10];
	if (dig_p[3] > 32767)
	{
		dig_p[3] -= 65536;
	}

	dig_p[4] = data[13] * 256 + data[12];
	if (dig_p[4] > 32767)
	{
		dig_p[4] -= 65536;
	}

	dig_p[5] = data[15] * 256 + data[14];
	if (dig_p[5] > 32767)
	{
		dig_p[5] -= 65536;
	}

	dig_p[6] = data[17] * 256 + data[16];
	if (dig_p[6] > 32767)
	{
		dig_p[6] -= 65536;
	}

	dig_p[7] = data[19] * 256 + data[18];
	if (dig_p[7] > 32767)
	{
		dig_p[7] -= 65536;
	}

	dig_p[8] = data[21] * 256 + data[20];
	if (dig_p[8] > 32767)
	{
		dig_p[8] -= 65536;
	}

	dig_p[9] = data[23] * 256 + data[22];
	if (dig_p[9] > 32767)
	{
		dig_p[9] -= 65536;
	}
}

void pressure::init_settings()
{
	std::array<u8, 2> config{};

	config[0] = 0xF4;
	config[1] = 0x27;
	write(fd, config.data(), config.size());

	config[0] = 0xF5;
	config[1] = 0xA0;
	write(fd, config.data(), config.size());

	sleep(1); // TODO: figure out if this is needed
}

} // namespace sensors
