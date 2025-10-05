cmake_minimum_required(VERSION 3.16)

# Version
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)

# Define root project
project(Maestro VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH} LANGUAGES CXX)

# Generate version
configure_file(
    ${CMAKE_SOURCE_DIR}/../include/version.h.in
    ${CMAKE_SOURCE_DIR}/model/version.h
)

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
    Bluetooth
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

include_directories(
    ${TAGLIB_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/core
    ${CMAKE_SOURCE_DIR}/extras
    ${CMAKE_SOURCE_DIR}/listitem
    ${CMAKE_SOURCE_DIR}/model
    ${CMAKE_SOURCE_DIR}/screen
)

link_libraries(
    Qt5::Core
    Qt5::Gui
    Qt5::Sql
    Qt5::Widgets
    Qt5::Multimedia
    Qt5::MultimediaWidgets
    Qt5::Gamepad
    Qt5::Bluetooth
    ${TAGLIB_LIBRARY}
    stdc++fs
)

# Executable
add_executable(Maestro ${SOURCES} ${APP_RESOURCES})

target_link_libraries(Maestro PRIVATE
    Maestro::Model
    Maestro::Extras
    Maestro::ListItem
    Maestro::Core
    Maestro::Screen
)

# Sub-project
add_subdirectory(model)
add_subdirectory(extras)
add_subdirectory(listitem)
add_subdirectory(screen)
add_subdirectory(core)
