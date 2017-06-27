cmake_minimum_required(VERSION 2.8.6)

include_directories(${${PROJECT_NAME}_SOURCE_DIR}/include)
message(STATUS "THIS INCLUDE dir " ${${PROJECT_NAME}_SOURCE_DIR}/include)
set(LIBRARY_OUTPUT_PATH ${${PROJECT_NAME}_SOURCE_DIR}/lib)

message(STATUS "THIS INCLUDE dir " ${${PROJECT_NAME}_SOURCE_DIR}/lib)
set(CMAKE_C_COMPILER g++)
set(SRC_LIST crc.cpp)
add_library(libcrc STATIC ${SRC_LIST})

