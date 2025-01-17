cmake_minimum_required(VERSION 2.8.12)
project(riscv-tiny-isa)
ADD_DEFINITIONS(-std=c++17 -g3)
find_package( Boost REQUIRED COMPONENTS iostreams )

file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB         SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(riscv-tiny-isa
    ${SRC}
    ${HEADERS}
)

target_link_libraries(riscv-tiny-isa ${Boost_LIBRARIES})
