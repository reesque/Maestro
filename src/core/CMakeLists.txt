add_library(Core STATIC
    controller.h
    controller.cpp
    database.h
    database.cpp
    mediaplayer.h
    mediaplayer.cpp
    settings.h
    settings.cpp
)

target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Core PUBLIC
    CommonDeps
    Maestro::Model
)

add_library(Maestro::Core ALIAS Core)
