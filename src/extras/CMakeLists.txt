set (SOURCES
    controllerlistwidget.cpp
    roundedprogressbarstyle.cpp
    scrolltextedit.cpp
)

set (HEADERS
    controllerlistwidget.h
    roundedprogressbarstyle.h
    scrolltextedit.h
)

add_library(Extras STATIC ${SOURCES} ${HEADERS})
add_library(Maestro::Extras ALIAS Extras)
