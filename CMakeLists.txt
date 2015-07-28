####################################################################################################
project(roadmap_2015-2)
cmake_minimum_required(VERSION 2.8)
####################################################################################################
#
INCLUDE_DIRECTORIES(
${CMAKE_SOURCE_DIR}/include
${CMAKE_SOURCE_DIR}/include/boost
)
#
if (${CMAKE_BUILD_TYPE} STREQUAL "debug")
    add_definitions(-DDEBUG_BUILD)
endif (${CMAKE_BUILD_TYPE} STREQUAL "debug")
#
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/source/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_SOURCE_DIR}/include/*.h)
#
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
#
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
