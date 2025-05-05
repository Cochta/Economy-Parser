cmake_minimum_required(VERSION 3.22)
project(economy_parser)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-DWIN32_LEAN_AND_MEAN)

option(BUILD_WEB "build for web" OFF)

option(BUILD_RELEASE "build in release" ON)

if (BUILD_WEB)
    add_compile_definitions(PLATFORM_WEB)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s ALLOW_MEMORY_GROWTH=1 --no-heap-copy")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif ()

find_package(raylib CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

set(ressource_dir "${CMAKE_SOURCE_DIR}/Ressource")

set(ressource_files)
file(GLOB_RECURSE RESSOURCE_FILES
            "Ressource/Files/*.json"
            "Ressource/Files/*.csv"
            "Ressource/Files/*.xml"
            "Ressource/Images/*.png"
            "Ressource/Images/*.jpg"
            )
list(APPEND ressource_files ${RESSOURCE_FILES})

# Common library
file(GLOB_RECURSE COMMON_FILES common/include/*.h common/src/*.cpp)
add_library(Common ${COMMON_FILES})
set_target_properties(Common PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(Common PUBLIC common/include/)
target_link_libraries(Common PUBLIC raylib fmt::fmt)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE Common)

set(RESSOURCE_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/Ressource/")

# Setup directories
if (BUILD_WEB)
    # Preload the 'Ressource' directory and mount it to '/ressource'
    set_target_properties(main PROPERTIES LINK_FLAGS "--preload-file Ressource")

    set(RESSOURCE_DEST "${CMAKE_CURRENT_BINARY_DIR}/Ressource/")
elseif(BUILD_RELEASE)
    set(RESSOURCE_DEST "${CMAKE_CURRENT_BINARY_DIR}/Release/Ressource/")
    file(COPY "${RESSOURCE_SOURCE}" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/Ressource/")
else()
    set(RESSOURCE_DEST "${CMAKE_CURRENT_BINARY_DIR}/Debug/Ressource/")
    file(COPY "${RESSOURCE_SOURCE}" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/Ressource/")
endif()

file(COPY "${RESSOURCE_SOURCE}" DESTINATION "${RESSOURCE_DEST}")
