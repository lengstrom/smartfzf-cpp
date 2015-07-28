cmake_minimum_required(VERSION 2.8)
project(smartfzf)

include_directories(include)

add_executable(
    smartfzf src/main.cc
             src/smartfzf.cc
)
