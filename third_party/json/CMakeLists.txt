add_library(json INTERFACE)
add_library(third_party::json ALIAS json)

target_include_directories(json INTERFACE include)
