#include "fundamental_types.h"
#include "server.h"
#include <cstdlib>
#include <iostream>
#include <spdlog/spdlog.h>
#include <unistd.h>

int main()
{
	spdlog::set_pattern("[%T] %^%v%$");
#ifndef NDEBUG
	spdlog::set_level(spdlog::level::debug);
#endif

	if (geteuid() != 0)
	{
		spdlog::error("This program must with root privelages");
		std::exit(EXIT_FAILURE);
	}

	try
	{
		auto provider = +[]() { return "{\"hello\": \"world\"}"; };
		server messenger{provider};
	}
	catch (const std::exception& e)
	{
		spdlog::error("An error has occured: {}", e.what());
		return EXIT_FAILURE;
	}
	catch (...)
	{
		spdlog::error("An unknown error has occured");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
