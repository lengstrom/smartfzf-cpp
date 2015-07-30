cmake_minimum_required(VERSION 2.8)
project(smartfzf)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS system filesystem)

include_directories(include ${Boost_INCLUDE_DIRS})

add_executable(
    smartfzf src/main.cc
             src/smartfzf.cc
)
target_link_libraries(smartfzf ${Boost_LIBRARIES})
