project(jimfeng-compiler)

cmake_minimum_required(VERSION 3.15)

set(ANTLR_CPP_RUNTIME_DIR
${PROJECT_SOURCE_DIR}/../antlr4-runtime
)

set(CMAKE_CXX_STANDARD 17)

set(SRC
    ${PROJECT_SOURCE_DIR}/main.cpp
)

aux_source_directory(${PROJECT_SOURCE_DIR}/frontend SRC)

include_directories(
    ${ANTLR_CPP_RUNTIME_DIR}/include/antlr4-runtime
    ${ANTLR_CPP_RUNTIME_DIR}/include/antlr4-runtime/atn
    ${ANTLR_CPP_RUNTIME_DIR}/include/antlr4-runtime/dfa
    ${ANTLR_CPP_RUNTIME_DIR}/include/antlr4-runtime/internal
    ${ANTLR_CPP_RUNTIME_DIR}/include/antlr4-runtime/misc
    ${ANTLR_CPP_RUNTIME_DIR}/include/antlr4-runtime/support 
)

add_executable(
    jimfeng-compiler ${SRC}
)

target_link_libraries(
    jimfeng-compiler ${ANTLR_CPP_RUNTIME_DIR}/libantlr4-runtime.a
)