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

find_package(raylib REQUIRED)
find_package(fmt REQUIRED)
find_package(imgui CONFIG REQUIRED)

set(data_dir "${CMAKE_SOURCE_DIR}/data")
set(ressource_dir "${CMAKE_SOURCE_DIR}/ressource")
 
set(data_files)
file(GLOB_RECURSE DATA_FILES
            "data/*.json"
            "data/*.csv"
            "data/*.xml"
            )
list(APPEND data_files ${DATA_FILES})

set(ressource_files)
file(GLOB_RECURSE RESSOURCE_FILES
            "ressource/*.png"
            "ressource/*.jpg"
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

if(BUILD_RELEASE)
    set(RESSOURCE_DEST "${CMAKE_CURRENT_BINARY_DIR}/Release/ressource/")
    set(DATA_DEST "${CMAKE_CURRENT_BINARY_DIR}/Release/data/")
else()
    set(RESSOURCE_DEST "${CMAKE_CURRENT_BINARY_DIR}/Debug/ressource/")
    set(DATA_DEST "${CMAKE_CURRENT_BINARY_DIR}/Debug/data/")
endif()

set(RESSOURCE_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/ressource/")
set(DATA_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/data/")

file(COPY "${RESSOURCE_SOURCE}" DESTINATION "${RESSOURCE_DEST}")
file(COPY "${DATA_SOURCE}" DESTINATION "${DATA_DEST}")

if (BUILD_WEB)
    # The local resources path needs to be mapped to /data virtual path
    string(APPEND data_dir "@data")
    string(APPEND ressource_dir "@ressource")
    set_target_properties(main PROPERTIES LINK_FLAGS "--preload-file ${data_dir}")
    set_target_properties(main PROPERTIES LINK_FLAGS "--preload-file ${ressource_dir}")
endif()
