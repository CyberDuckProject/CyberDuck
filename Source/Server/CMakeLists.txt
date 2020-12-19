add_executable(
	Server
	Main.cpp
	Json.h
	Json.cpp
	Server.h
	Server.cpp
)

# Dependencies
target_link_libraries(
	Server PRIVATE
	CyberDuck::Sensors
	ThirdParty::Json
	ThirdParty::Beast
)
