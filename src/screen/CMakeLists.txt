qt5_wrap_ui(UI_HEADERS
    menu.ui
)

add_library(Screen STATIC
    ${UI_HEADERS}
    albummenu.h
    albummenu.cpp
    artistfiltermenu.h
    artistfiltermenu.cpp
    artistmenu.h
    artistmenu.cpp
    controllermenu.h
    controllermenu.cpp
    mainmenu.h
    mainmenu.cpp
    menu.h
    musicmenu.h
    musicmenu.cpp
    nowplaying.h
    nowplaying.cpp
    nowplaying.ui
    reindexscreen.h
    reindexscreen.cpp
    reindexscreen.ui
    screen.h
    screen.cpp
    settingmenu.h
    settingmenu.cpp
    songsmenu.h
    songsmenu.cpp
    statusbar.h
    statusbar.cpp
    statusbar.ui
)

target_include_directories(Screen PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)
target_link_libraries(Screen PUBLIC
    CommonDeps
    Maestro::ListItem
    Maestro::Core
)

add_library(Maestro::Screen ALIAS Screen)
