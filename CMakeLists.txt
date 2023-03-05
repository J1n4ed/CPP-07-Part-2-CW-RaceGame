cmake_minimum_required(VERSION 3.14.0)
set (CMAKE_CXX_STANDARD 20)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

project(RaceGame)

include_directories(
        ${PROJECT_SOURCE_DIR}/RaceApp/headers
        ${PROJECT_SOURCE_DIR}/RaceApp/src
        ${PROJECT_SOURCE_DIR}/RaceLib/interfaces        
        ${PROJECT_SOURCE_DIR}/RaceLib/includes
)

link_directories(${PROJECT_SOURCE_DIR}/RaceApp/interaces)

file(GLOB Lib_SRCS
        "${PROJECT_SOURCE_DIR}/RaceLib/interfaces/*.ixx"
        "${PROJECT_SOURCE_DIR}/RaceLib/includes/*.h"
        )

file(GLOB App_SRCS
        "${PROJECT_SOURCE_DIR}/RaceApp/headers/*.h"
        "${PROJECT_SOURCE_DIR}/RaceApp/src/*.cpp"
        )
		
configure_file(${PROJECT_SOURCE_DIR}/RaceApp/resources/botnames.txt botnames.txt COPYONLY)
configure_file(${PROJECT_SOURCE_DIR}/RaceApp/resources/botcallsigns.txt botcallsigns.txt COPYONLY)

add_library(RaceLib SHARED ${Lib_SRCS} "RaceLib/includes/RaceLibExceptions.h")
add_executable(RaceGame ${App_SRCS} "RaceLib/includes/RaceLibExceptions.h")

target_link_libraries(RaceGame RaceLib)