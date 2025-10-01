add_library(ListItem STATIC
    artworkmenulistitem.h
    artworkmenulistitem.cpp
    artworkmenulistitem.ui
    basemenulistitem.h
    basemenulistitem.cpp
    detailedmenulistitem.h
    detailedmenulistitem.cpp
    detailedmenulistitem.ui
    menulistitem.h
    menulistitem.cpp
    menulistitem.ui
    menuwithtogglelistitem.h
    menuwithtogglelistitem.cpp
    menuwithtogglelistitem.ui
    settingssliderlistitem.h
    settingssliderlistitem.cpp
    settingssliderlistitem.ui
)

target_include_directories(ListItem PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ListItem PUBLIC
    CommonDeps
    Maestro::Model
    Maestro::Extras
)

add_library(Maestro::ListItem ALIAS ListItem)
