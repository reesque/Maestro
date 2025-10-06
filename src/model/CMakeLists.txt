set (HEADERS
    datastruct.h
    menuentry.h
    version.h
)

add_library(Model STATIC ${HEADERS})
add_library(Maestro::Model ALIAS Model)
