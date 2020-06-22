project(mymath_sample)

add_executable(mymath_sample main.cpp)
target_compile_options(mymath_sample PRIVATE 
    $<$<OR:$<STREQUAL:"${CMAKE_CXX_COMPILER_ID}","GNU">,$<STREQUAL:"${CMAKE_CXX_COMPILER_ID}","Clang">>:-Wall -Wextra -Wno-long-long -pedantic -fsanitize=address -fno-omit-frame-pointer> 
)

target_link_options(mymath_sample PRIVATE 
    $<$<OR:$<STREQUAL:"${CMAKE_CXX_COMPILER_ID}","GNU">,$<STREQUAL:"${CMAKE_CXX_COMPILER_ID}","Clang">>:-fsanitize=address -fno-omit-frame-pointer> 
)

target_compile_features(mymath_sample PUBLIC
    cxx_std_14
)

target_link_libraries(mymath_sample
    mymathlib
)

add_custom_target(run_mymath_sample
    COMMAND mymath_sample
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    DEPENDS mymath_sample
)
