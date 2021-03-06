cmake_minimum_required(VERSION 3.12)
project(graphs CXX)

set(SOURCE ${PROJECT_SOURCE_DIR}/src)
set(INCLUDE ${PROJECT_SOURCE_DIR}/include)
set(DATA ${PROJECT_SOURCE_DIR}/data)

set(GRAPHS_SOURCES
        ${SOURCE}/graph.cpp
        ${SOURCE}/map.cpp
        ${SOURCE}/geojson.cpp
        ${SOURCE}/dmatrix.cpp
        ${SOURCE}/clustering.cpp
        ${SOURCE}/color.cpp
        ${SOURCE}/assessment.cpp
        ${SOURCE}/planning.cpp
        ${SOURCE}/main.cpp
        )

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

# Define build type.
set(CMAKE_BUILD_TYPE "Debug")

add_executable(graphs ${GRAPHS_SOURCES})

target_include_directories(graphs PRIVATE ${SOURCE})
target_include_directories(graphs PRIVATE ${INCLUDE})

set_property(TARGET graphs PROPERTY CXX_STANDARD 17)

# Required dynamic-link libraries.
find_package(fmt REQUIRED)
find_package(Osmium REQUIRED COMPONENTS pbf)
find_package(ZLIB REQUIRED)
find_package(Threads REQUIRED)
find_package(Boost REQUIRED serialization)

# Move necessary data files to build directory.
configure_file(data/Graph.csv ${CMAKE_CURRENT_BINARY_DIR}/Graph.csv COPYONLY)
configure_file(data/NNMap.pbf ${CMAKE_CURRENT_BINARY_DIR}/NNMap.pbf COPYONLY)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    configure_file(data/VNMap.pbf ${CMAKE_CURRENT_BINARY_DIR}/VNMap.pbf COPYONLY)
endif ()

target_compile_options(graphs PRIVATE -Werror -Wall -Wextra)
if (CMAKE_BUILD_TYPE EQUAL "Release")
    target_compile_options(graphs PRIVATE -O3)
endif ()

target_link_libraries(graphs PUBLIC
        fmt::fmt
        ${OSMIUM_IO_LIBRARIES}
        ${ZLIB_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
        ${Boost_LIBRARIES})
