#include "server.h"
#include <spdlog/spdlog.h>
#include <iostream>

int main()
{
	spdlog::set_pattern("[%T] %^%v%$");
#ifndef NDEBUG
	spdlog::set_level(spdlog::level::debug);
#endif

	if (geteuid() != 0)
	{
		spdlog::error("This program must with root privelages");
		return EXIT_FAILURE;
	}

	try
	{
		spdlog::info("Initializing server");
		auto provider{[]() { return "{\"hello\": \"world\"}"; }};
		server messenger{provider};

		spdlog::info("Initialization finished");
		std::cin.get();
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
