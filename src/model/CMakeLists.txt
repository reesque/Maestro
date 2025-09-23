add_library(Model STATIC
    datastruct.h
    menuentry.h
)

target_include_directories(Model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Model PUBLIC CommonDeps)

add_library(Maestro::Model ALIAS Model)
