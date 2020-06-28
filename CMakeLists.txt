cmake_minimum_required(VERSION 3.17)

set(AVR_CROSS_COMPILE FALSE)
set(CMAKE_CXX_EXTENSIONS OFF)

project(converalls_sample C)

add_library(mymath)
target_include_directories(mymath
    PUBLIC 
    include/mymath
)

add_library(driver)
target_include_directories(driver
    PUBLIC
    include/driver
)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(cli)

enable_testing()
add_subdirectory(test)

add_custom_target(ci
    DEPENDS
        run_mymath_sample
        $<$<CONFIG:Debug>:debug_test>
        $<$<NOT:$<CONFIG:Debug>>:release_test>
)
