cmake_minimum_required(VERSION 3.5)
project(dedacker)

set(CMAKE_CXX_STANDARD 11)

# add source files, usualy under src/, also add the include/ and lib/


#aux_source_directory(${PROJECT_SOURCE_DIR}/src SOURCE_FILES)
#include_directories(${PROJECT_SOURCE_DIR}/include)
#link_directories(${PROJECT_SOURCE_DIR}/lib)

# find all file recurse, DO NOT recurse build folder
file(GLOB_RECURSE SOURCES src/*.cpp lib/*.cpp )
file(GLOB_RECURSE HEADERS include/*.h lib/*.h)

find_package(OpenCV 3.0)
if (NOT OpenCV_FOUND)
    message(FATAL_ERROR "OpenCV > 3.0 not found.")
endif ()

set(BUILD_SHARED_LIBS OFF)

add_executable(dedacker ${SOURCES} ${HEADERS})
target_link_libraries(dedacker ${OpenCV_LIBS})