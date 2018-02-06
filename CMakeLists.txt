
add_library(CoreString
    CoreString/libs/asprintf/asprintf.cpp
    CoreString/libs/asprintf/vasprintf-c99.cpp
    CoreString/src/CoreString.cpp
)

target_include_directories(CoreString PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
