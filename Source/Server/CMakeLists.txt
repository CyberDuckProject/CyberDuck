add_executable(
	Server
	Main.cpp
)

# Dependencies
target_link_libraries(
	Server PRIVATE
	ThirdParty::Json
)
