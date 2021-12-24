cmake_minimum_required(VERSION 3.13)
project(pamalert)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

find_package(CURL REQUIRED)
find_package(PAM REQUIRED)

add_library(pamalert SHARED src/main.c)
target_link_libraries(pamalert ${CURL_LIBRARIES} ${PAM_LIBRARIES})