project(compiler)

cmake_minimum_required(VERSION 3.15)

set(ANTLR_CPP_RUNTIME_DIR ${PROJECT_SOURCE_DIR}/antlr4-runtime )
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
file(GLOB_RECURSE SRC ${SOURCE_DIR}/*.cpp)

add_executable(
    compiler ${SRC}
)

target_include_directories(compiler PRIVATE
    ${ANTLR_CPP_RUNTIME_DIR}
    ${SOURCE_DIR}/frontend/
    ${SOURCE_DIR}/frontend/generated/
    ${SOURCE_DIR}/common/
    ${SOURCE_DIR}/backend/
    ${SOURCE_DIR}/backend/mach/
    ${SOURCE_DIR}/backend/mach/arch/
)

target_link_libraries(compiler antlr4-runtime)

