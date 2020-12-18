add_executable(
	Server
	Main.cpp
	FundamentalTypes.h
	Json.h
	Json.cpp
)

# Dependencies
target_link_libraries(
	Server PRIVATE
	ThirdParty::Json
)
