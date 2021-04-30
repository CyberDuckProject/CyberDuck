#include "environment.h"
#include "server.h"
#include <iostream>
#include <spdlog/spdlog.h>

i32 main()
{
	spdlog::set_pattern("[%T] %^%v%$");
#ifndef NDEBUG
	spdlog::set_level(spdlog::level::debug);
#endif

	if (geteuid() != 0)
	{
		spdlog::error("Fatal error: insufficient program privelages");
		return EXIT_FAILURE;
	}

	try
	{
		spdlog::info("Initializing sensors");
		environment environment{};

		spdlog::info("Initializing server");
		auto provider{[&environment]() { return environment.json(); }};
		server messenger{provider};

		spdlog::info("Initialization finished");
		std::cin.get();
	}
	catch (const std::exception& e)
	{
		spdlog::error("Fatal error: {}", e.what());
		return EXIT_FAILURE;
	}
	catch (...)
	{
		spdlog::error("Unknown fatal error");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
