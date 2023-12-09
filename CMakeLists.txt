cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(SPF LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME} main.cpp)

include_directories(${SPF_SOURCE_DIR}/extern/eigen)
include_directories(${SPF_SOURCE_DIR}/extern/rapidcsv/src)

set(PJT_PATH ${SPF_SOURCE_DIR})
configure_file(PROJECT_DIR.h.in ${SPF_SOURCE_DIR}/PROJECT_DIR.h)
