add_library(ina260 INTERFACE)

target_sources(ina260 INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/ina260.cpp
        )

target_include_directories(ina260 INTERFACE ${CMAKE_CURRENT_LIST_DIR})

# Pull in pico libraries that we need
target_link_libraries(ina260 INTERFACE pico_stdlib hardware_spi)