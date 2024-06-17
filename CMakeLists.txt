cmake_minimum_required(VERSION 3.14)

project(banking-system)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(GTest REQUIRED)

include_directories(include/)

add_executable(main
        src/main.cpp
        src/unit_tests.cpp
        src/Person.cpp
        src/Account.cpp
)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wpedantic")

set(CMAKE_CXX_FLAGS_RELEASE "-O3")

target_link_libraries(main
        GTest::GTest
        GTest::Main
)
