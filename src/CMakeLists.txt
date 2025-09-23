cmake_minimum_required(VERSION 3.16)
project(Maestro LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Qt automatic handling
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Resource
set(APP_RESOURCES assets.qrc)

# Find taglib
find_path(TAGLIB_INCLUDE_DIR taglib/tag.h PATHS /usr/include)
find_library(TAGLIB_LIBRARY tag PATHS /usr/lib)

# Find Qt
find_package(Qt5 REQUIRED COMPONENTS
    Core
    Gui
    Sql
    Widgets
    Multimedia
    MultimediaWidgets
    Gamepad
)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

set(SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

# Executable
add_executable(Maestro ${SOURCES} ${APP_RESOURCES})

# Sub-project
add_subdirectory(model)
add_subdirectory(extras)
add_subdirectory(listitem)
add_subdirectory(screen)
add_subdirectory(core)

# Common dependencies
add_library(CommonDeps INTERFACE)
target_include_directories(CommonDeps INTERFACE ${TAGLIB_INCLUDE_DIR})
target_link_libraries(CommonDeps INTERFACE
    Qt5::Core
    Qt5::Gui
    Qt5::Sql
    Qt5::Widgets
    Qt5::Multimedia
    Qt5::MultimediaWidgets
    Qt5::Gamepad
    ${TAGLIB_LIBRARY}
    stdc++fs
)

# Link all libraries
target_link_libraries(Maestro PRIVATE
    CommonDeps
    Maestro::Model
    Maestro::Extras
    Maestro::ListItem
    Maestro::Core
    Maestro::Screen
)
