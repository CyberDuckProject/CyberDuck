add_library(beast INTERFACE)
add_library(third_party::beast ALIAS beast)

target_include_directories(beast INTERFACE include)

find_package(Threads REQUIRED)
target_link_libraries(
	beast INTERFACE
	Threads::Threads
)
