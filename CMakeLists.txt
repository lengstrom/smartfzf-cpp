cmake_minimum_required(VERSION 2.8)
project(smartfzf)

enable_testing()

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS system filesystem
    unit_test_framework)
find_package(Curses REQUIRED)

include_directories(include ${Boost_INCLUDE_DIRS})
include_directories(include ${CURSES_INCLUDE_DIR})

add_executable(
    smartfzf src/main.cc
             src/smartfzf.cc
             src/renderer.cc
)

target_link_libraries(smartfzf ${Boost_LIBRARIES})
target_link_libraries(smartfzf ${CURSES_LIBRARIES})

file(GLOB tests test/*.cc)
foreach(test ${tests})
    get_filename_component(bname ${test} NAME_WE)
    add_executable(${bname} ${test} src/smartfzf.cc)
    target_link_libraries(${bname} ${Boost_LIBRARIES})
    target_link_libraries(${bname} ${CURSES_LIBRARIES})
    set_target_properties(${bname} PROPERTIES 
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/test)
    add_test(NAME ${bname} 
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/test
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test/${bname} 
        --catch_system_error=yes --report_level=detailed
        --log_level=all
        )
endforeach(test)

set_property(TARGET smartfzf PROPERTY CXX_STANDARD 11)
