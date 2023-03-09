cmake_minimum_required(VERSION 3.25)

set (CMAKE_CXX_STANDARD 20)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(BUILD_SHARED_LIBS:BOOL=OFF)

if (CMAKE_VERSION VERSION_LESS "3.26")
    # 3.25
    set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "3c375311-a3c9-4396-a187-3227ef642046")
elseif (CMAKE_VERSION VERSION_LESS "3.27")
    # 3.26
    set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "2182bf5c-ef0d-489a-91da-49dbc3090d2a")
else ()
    message(FATAL_ERROR "See `https://github.com/Kitware/CMake/blob/v${CMAKE_VERSION}/Help/dev/experimental.rst`.")
endif (CMAKE_VERSION VERSION_LESS "3.26")
# turn on the dynamic depends for ninja
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP ON)

project(RaceGame)

include_directories(
        RaceApp/headers
        RaceApp/src
        RaceLib/interfaces        
        RaceLib/includes
)

link_directories(RaceApp/interaces)

file(GLOB Lib_SRCS
        "RaceLib/interfaces/*.ixx"
        )

file(GLOB App_SRCS
        "RaceApp/src/*.cpp"
        )
		
configure_file(RaceApp/resources/botnames.txt Debug/botnames.txt COPYONLY)
configure_file(RaceApp/resources/botcallsigns.txt Debug/botcallsigns.txt COPYONLY)

add_library(RaceLib STATIC)

target_sources(
        RaceLib
        PRIVATE
        FILE_SET module_files
        TYPE CXX_MODULES
        BASE_DIRS "${PROJECT_SOURCE_DIR}"
        FILES

        ${PROJECT_SOURCE_DIR}/RaceLib/interfaces/RaceLib.ixx
)

add_executable(RaceGame ${App_SRCS})

target_link_libraries(RaceGame RaceLib)