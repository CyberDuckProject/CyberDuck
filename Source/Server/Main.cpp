#include "Server.h"
#include <cstdlib>

i32 main()
{
	init_server(9080);

	while (true)
	{
		handle_requests();
	}

	return EXIT_SUCCESS;
}
