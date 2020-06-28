project(mymath_sample C)

add_executable(mymath_sample main.c)
target_compile_options(mymath_sample PRIVATE 
    $<$<AND:$<OR:$<STREQUAL:"${CMAKE_CXX_COMPILER_ID}","GNU">,$<STREQUAL:"${CMAKE_CXX_COMPILER_ID}","Clang">>,$<STREQUAL:"${AVR_CROSS_COMPILE}","FALSE">>:-Wall -Wextra -Wno-long-long -pedantic -fsanitize=address -fno-omit-frame-pointer> 
)

target_link_options(mymath_sample PRIVATE 
    $<$<AND:$<OR:$<STREQUAL:"${CMAKE_CXX_COMPILER_ID}","GNU">,$<STREQUAL:"${CMAKE_CXX_COMPILER_ID}","Clang">>,$<STREQUAL:"${AVR_CROSS_COMPILE}","FALSE">>:-fsanitize=address -fno-omit-frame-pointer>
)

target_compile_features(mymath_sample PUBLIC
    c_std_99
)

target_link_libraries(mymath_sample
    mymath
)

add_custom_target(run_mymath_sample
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    DEPENDS mymath_sample
)
