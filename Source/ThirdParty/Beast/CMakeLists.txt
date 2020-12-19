add_library(Beast INTERFACE)

# ThirdParty namespace
add_library(ThirdParty::Beast ALIAS Beast)

# Include directory
target_include_directories(Beast INTERFACE Include)

# Dependencies
find_package(Threads REQUIRED)
target_link_libraries(
	Beast INTERFACE
	Threads::Threads
)
