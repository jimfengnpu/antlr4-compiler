project(compiler)

cmake_minimum_required(VERSION 3.15)

set(ANTLR_CPP_RUNTIME_DIR ${PROJECT_SOURCE_DIR}/antlr4-runtime )
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
file(GLOB_RECURSE SRC ${SRC_DIR}/*.cpp)
include_directories(${SRC_DIR})
include_directories(${ANTLR_CPP_RUNTIME_DIR})
add_executable(
    compiler ${SRC}
)
target_link_libraries(compiler antlr4-runtime)

