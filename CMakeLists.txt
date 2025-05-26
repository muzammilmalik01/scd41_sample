cmake_minimum_required(VERSION 3.20.0)


set(DTC_OVERLAY_FILE "app/boards/nrf52840dk_nrf52840.overlay")

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})


# add_dependencies(scd4x, offsets_h)
zephyr_include_directories(${CMAKE_CURRENT_SOURCE_DIR}/drivers/sensor/scd4x)
zephyr_include_directories(include/zephyr)
zephyr_include_directories(dts/bindings)

zephyr_library()
zephyr_library_sources(drivers/sensor/scd4x/scd4x.c)

project(scd41_sample)

target_sources(app PRIVATE src/main.c)
