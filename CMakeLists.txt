project(compiler)

cmake_minimum_required(VERSION 3.15)

set(ANTLR_CPP_RUNTIME_DIR ${PROJECT_SOURCE_DIR}/antlr4-runtime )
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src )

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE LIB_SRC ${ANTLR_CPP_RUNTIME_DIR}/*.cpp)
file(GLOB_RECURSE SRC ${SRC_DIR}/*.cpp)
include_directories(${ANTLR_CPP_RUNTIME_DIR})
include_directories(${SRC_DIR})

add_executable(
    compiler ${SRC} ${LIB_SRC}
)

