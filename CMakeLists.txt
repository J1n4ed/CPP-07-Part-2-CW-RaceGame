cmake_minimum_required(VERSION 3.14.0)
set (CMAKE_CXX_STANDARD 20)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

project(RaceGame)

include_directories(
        ${PROJECT_SOURCE_DIR}/RaceApp/headers
        ${PROJECT_SOURCE_DIR}/RaceApp/src
        ${PROJECT_SOURCE_DIR}/RaceLib/interface
)

link_directories(${PROJECT_SOURCE_DIR}/RaceApp/interace)

file(GLOB Lib_SRCS
        "${PROJECT_SOURCE_DIR}/RaceLib/interface/*.ixx"
        )

file(GLOB App_SRCS
        "${PROJECT_SOURCE_DIR}/RaceApp/headers/*.h"
        "${PROJECT_SOURCE_DIR}/RaceApp/src/*.cpp"
        )
		
configure_file(/resources/botnames.txt botnames.txt COPYONLY)
configure_file(/resources/botcallsigns.txt botcallsigns.txt COPYONLY)

add_library(RaceLib SHARED ${Lib_SRCS})
add_executable(RaceGame ${App_SRCS})

target_link_libraries(RaceGame RaceLib)