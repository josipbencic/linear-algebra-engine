cmake_minimum_required(VERSION 3.8)

project(numerical CXX)

add_subdirectory("src")
add_subdirectory("app")

option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(tests)
endif()
