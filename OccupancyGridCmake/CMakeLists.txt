cmake_minimum_required(VERSION 2.8)

PROJECT(ogrid)

find_package(OpenCV REQUIRED)

set(NAME_SRC src/main.cpp)

# set(NAME_HEADERS include/)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_executable(ogrid ${NAME_SRC})
target_link_libraries(ogrid ${OpenCV_LIBS})
