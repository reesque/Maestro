qt5_wrap_ui(UI_HEADERS
    menu.ui
)

set (SOURCES
    albummenu.cpp
    artistfiltermenu.cpp
    artistmenu.cpp
    bluetoothmenu.cpp
    bluetoothscanmenu.cpp
    bluetoothpairscreen.cpp
    controllermenu.cpp
    mainmenu.cpp
    musicmenu.cpp
    nowplaying.cpp
    reindexscreen.cpp
    screen.cpp
    settingmenu.cpp
    songsmenu.cpp
    statusbar.cpp
)

set (HEADERS
    albummenu.h
    artistfiltermenu.h
    artistmenu.h
    bluetoothmenu.h
    bluetoothscanmenu.h
    bluetoothpairscreen.h
    controllermenu.h
    mainmenu.h
    menu.h
    musicmenu.h
    nowplaying.h
    reindexscreen.h
    screen.h
    settingmenu.h
    songsmenu.h
    statusbar.h
)

set (FORMS
    bluetoothpair.ui
    nowplaying.ui
    reindexscreen.ui
    statusbar.ui
    menu.ui
)

link_libraries(
    Maestro::Core
    Maestro::ListItem
    Maestro::Extras
)

add_library(Screen STATIC ${UI_HEADERS} ${SOURCES} ${HEADERS} ${FORMS})

target_include_directories(Screen PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}
)

add_library(Maestro::Screen ALIAS Screen)
