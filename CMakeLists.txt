##~---------------------------------------------------------------------------##
##                     _______  _______  _______  _     _                     ##
##                    |   _   ||       ||       || | _ | |                    ##
##                    |  |_|  ||       ||   _   || || || |                    ##
##                    |       ||       ||  | |  ||       |                    ##
##                    |       ||      _||  |_|  ||       |                    ##
##                    |   _   ||     |_ |       ||   _   |                    ##
##                    |__| |__||_______||_______||__| |__|                    ##
##                             www.amazingcow.com                             ##
##  File      : CMakeLists.txt                                                ##
##  Project   : CoreString                                                    ##
##  Date      : Feb 19, 2018                                                  ##
##  License   : GPLv3                                                         ##
##  Author    : n2omatt <n2omatt@amazingcow.com>                              ##
##  Copyright : AmazingCow - 2018                                             ##
##                                                                            ##
##  Description :                                                             ##
##                                                                            ##
##---------------------------------------------------------------------------~##


cmake_minimum_required(VERSION 3.5)

##------------------------------------------------------------------------------
## Project Settings.
project(CoreString)


##------------------------------------------------------------------------------
## Sources.
add_library(CoreString
    CoreString/libs/asprintf/asprintf.cpp
    CoreString/libs/asprintf/vasprintf-c99.cpp
    CoreString/src/CoreString.cpp
)


##------------------------------------------------------------------------------
## Include directories.
target_include_directories(CoreString PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


##------------------------------------------------------------------------------
## Dependencies.
target_link_libraries(CoreString LINK_PUBLIC CoreAssert)
