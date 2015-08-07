cmake_minimum_required(VERSION 3.0) # for multiline strings

# ensure we're in the build directory

if("${CMAKE_CURRENT_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_BINARY_DIR}")
    MESSAGE(FATAL_ERROR "The current directory is ${CMAKE_CURRENT_BINARY_DIR}.\
    Please delete the temporary cmake files `rm -rf CMakeCache.txt CMakeFiles/`,\
    `cd` to the build directory (`cd build/`)\
    and run the script again (`cmake ..`).")
else()
    MESSAGE(STATUS "Current directory: ${CMAKE_CURRENT_BINARY_DIR}")
endif()

project(smartfzf)

enable_testing()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_BINARY_DIR}/modules/")
set(Boost_USE_STATIC_LIBS ON)

find_package(Boost REQUIRED COMPONENTS system filesystem
    unit_test_framework)
find_package(Curses REQUIRED)
find_package(Readline REQUIRED)

include_directories(include ${Boost_INCLUDE_DIRS} 
    ${CURSES_INCLUDE_DIR} ${READLINE_INCLUDE_DIR})

add_executable(
    smartfzf src/main.cc
             src/smartfzf.cc
             src/renderer.cc
             src/fs.cc
)

target_link_libraries(smartfzf ${Boost_LIBRARIES} ${CURSES_LIBRARIES}
    ${READLINE_LIBRARY})

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
