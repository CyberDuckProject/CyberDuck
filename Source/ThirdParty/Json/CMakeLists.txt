add_library(Json INTERFACE)

# ThirdParty namespace
add_library(ThirdParty::Json ALIAS Json)

# Include directory
target_include_directories(Json INTERFACE Include)
