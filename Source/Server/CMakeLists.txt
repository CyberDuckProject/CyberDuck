add_executable(
	Server
	Main.cpp
	FundamentalTypes.h
	Json.h
	Json.cpp
	AnalogPin.h
	AnalogPin.cpp
	Utilities.h
	Utilities.cpp
)

# Dependencies
target_link_libraries(
	Server PRIVATE
	ThirdParty::Json
)
