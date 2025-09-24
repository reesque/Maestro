add_library(Extras STATIC
    roundedprogressbarstyle.h
    roundedprogressbarstyle.cpp
    scrolltextedit.h
    scrolltextedit.cpp
)

target_include_directories(Extras PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Extras PUBLIC CommonDeps)

add_library(Maestro::Extras ALIAS Extras)
