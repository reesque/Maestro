set (SOURCES
    controller.cpp
    database.cpp
    mediaplayer.cpp
    settings.cpp
)

set (HEADERS
    controller.h
    database.h
    mediaplayer.h
    settings.h
)

link_libraries(
    Maestro::Model
)

add_library(Core STATIC ${SOURCES} ${HEADERS})
add_library(Maestro::Core ALIAS Core)
