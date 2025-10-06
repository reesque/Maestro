set (SOURCES
    artworkmenulistitem.cpp
    detailedmenulistitem.cpp
    menulistitem.cpp
    menuwithtogglelistitem.cpp
    settingssliderlistitem.cpp
    twosidedlistitem.cpp
)

set (HEADERS
    artworkmenulistitem.h
    basemenulistitem.h
    detailedmenulistitem.h
    menulistitem.h
    menuwithtogglelistitem.h
    settingssliderlistitem.h
    twosidedlistitem.h
)

set (FORMS
    artworkmenulistitem.ui
    detailedmenulistitem.ui
    menulistitem.ui
    menuwithtogglelistitem.ui
    settingssliderlistitem.ui
    twosidedlistitem.ui
)

link_libraries(
    Maestro::Model
    Maestro::Extras
)

add_library(ListItem STATIC ${SOURCES} ${HEADERS} ${FORMS})
add_library(Maestro::ListItem ALIAS ListItem)
