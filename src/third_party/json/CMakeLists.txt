add_library(json INTERFACE)

# third_party namespace
add_library(third_party::json ALIAS json)

# Include directory
target_include_directories(json INTERFACE include)
