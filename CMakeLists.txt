cmake_minimum_required(VERSION 2.8)
project(ip_filter LANGUAGES CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(ip_filter ip_filter.cpp)
target_link_libraries(ip_filter ${CONAN_LIBS})
