add_library(beast INTERFACE)

# third_party namespace
add_library(third_party::beast ALIAS beast)

# Include directory
target_include_directories(beast INTERFACE include)

# Dependencies
find_package(Threads REQUIRED)
target_link_libraries(
	beast INTERFACE
	Threads::Threads
)
