####################################################################################################
project(roadmap_2015-2)
cmake_minimum_required(VERSION 2.8)
####################################################################################################
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wcast-align -Wcast-qual -Werror -Wextra \
-Wnon-virtual-dtor -Wno-unused-parameter -Wshadow -Wwrite-strings -fno-omit-frame-pointer \
-fno-optimize-sibling-calls -fno-strict-aliasing -fsigned-char -fstrict-overflow -std=c++11 \
-Wno-ignored-qualifiers -Wno-c++0x-compat -Wno-array-bounds -Wno-empty-body"
) # SET CMAKE_CXX_FLAGS
message("CMAKE_CXX_FLAGS are ${CMAKE_CXX_FLAGS}")
#
INCLUDE_DIRECTORIES(
${CMAKE_SOURCE_DIR}/include
${CMAKE_SOURCE_DIR}/include/boost
${CMAKE_SOURCE_DIR}/include/boost/signals
${CMAKE_SOURCE_DIR}/include/boost/bind
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
