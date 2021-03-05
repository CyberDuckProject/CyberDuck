add_library(
	bme280 STATIC
	include/bme280_defs.h
	include/bme280.h
	src/bme280.c
)

add_library(third_party::bme280 ALIAS bme280)

target_include_directories(bme280 PUBLIC include)

target_link_libraries(bme280 PUBLIC i2c)
