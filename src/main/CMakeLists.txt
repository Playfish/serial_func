cmake_minimum_required(VERSION 2.8.6)

######main.cpp 
SET(EXECUTABLE_OUTPUT_PATH ${${PROJECT_NAME}_SOURCE_DIR}/bin)

set(SRC_LIST main.cpp)

include_directories(${${PROJECT_NAME}_SOURCE_DIR}/include)
link_directories(${${PROJECT_NAME}_SOURCE_DIR}/lib)
add_executable(serial ${SRC_LIST})
target_link_libraries(serial libserial libcrc)
