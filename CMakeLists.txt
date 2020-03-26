cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(libzcw)

option(ZCW_BUILD_STATIC "BUILD STATIC LIBRARIES" ON)
option(ZCW_BUILD_SHARED "BUILD SHARED LIBRARIES" ON)

if(NOT ZCW_BUILD_SHARED AND NOT ZCW_BUILD_STATIC)
    message(SEND_ERROR "You need to build at least one flavor of libzcw")
endif()

set(CMAKE_CXX_STANDARD 20)

set(LIBRARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)

include_directories(${LIBRARY_DIR} ${LIBRARY_DIR}/common)

set(Sources
        ${LIBRARY_DIR}/zcw.cc
        ${LIBRARY_DIR}/enc/encoder_dict.cc
        ${LIBRARY_DIR}/enc/encoder.cc)

set(Headers
        ${LIBRARY_DIR}/zcw.h
        ${LIBRARY_DIR}/enc/encoder_dict.h
        ${LIBRARY_DIR}/common/dictionary.h
        ${LIBRARY_DIR}/enc/word.h
        ${LIBRARY_DIR}/common/internal.h
        ${LIBRARY_DIR}/enc/encoder.h)

if (ZCW_BUILD_SHARED)
    add_library(libzcw_shared SHARED ${Sources} ${Headers})
endif ()
if (ZCW_BUILD_STATIC)
    add_library(libzcw_static STATIC ${Sources} ${Headers})
endif ()

if (MSVC)
    if (ZCW_BUILD_SHARED)
        set_property(TARGET libzcw_shared APPEND PROPERTY COMPILE_DEFINITIONS "ZCW_DLL_EXPORT=1")
    endif ()
endif ()

add_subdirectory(tools/cli)