cmake_minimum_required(VERSION 3.17)

set(AVR_CROSS_COMPILE FALSE)
set(CMAKE_CXX_EXTENSIONS OFF)

project(converalls_sample C)

add_library(mymathlib)
target_include_directories(mymathlib
    PUBLIC 
    include/mymath
)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(cli)

#enable_testing()
add_subdirectory(test)

add_custom_target(ci
    DEPENDS
        run_mymath_sample
        #        $<$<CONFIG:Debug>:debug_test>
        $<$<NOT:$<CONFIG:Debug>>:release_test>
)
