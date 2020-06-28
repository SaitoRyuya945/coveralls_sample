project(tests)

include(ExternalProject)

set(GTEST_BUILD_DIR ${CMAKE_BINARY_DIR}/gtest)
set(GTEST_INSTALL_DIR ${CMAKE_SOURCE_DIR}/gtest)
set(GTEST_INCLUDE_DIR ${GTEST_INSTALL_DIR}/include)
set(GTEST_LIB_DIR ${GTEST_INSTALL_DIR}/lib)

find_package(Threads REQUIRED)

ExternalProject_Add(googletest
    URL https://github.com/google/googletest/archive/release-1.8.1.zip
    PREFIX ${GTEST_BUILD_DIR}
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${GTEST_INSTALL_DIR} -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
)

add_library(gtest IMPORTED STATIC GLOBAL)

set_target_properties(gtest PROPERTIES
    IMPORTED_LOCATION ${GTEST_LIB_DIR}/libgtest.a
    INTERFACE_LINK_LIBRARIES ${CMAKE_THREAD_LIBS_INIT}
)

add_library(gmock IMPORTED STATIC GLOBAL)

set_target_properties(gmock PROPERTIES
    IMPORTED_LOCATION ${GTEST_LIB_DIR}/libgmock.a
    INTERFACE_LINK_LIBRARIES ${CMAKE_THREAD_LIBS_INIT}
)

function(add_unit_test target_name name)
    target_sources(${target_name}
        PRIVATE
        ${name}.cpp
    )
    add_test(
        NAME ${name}
        COMMAND ${name}
    )
endfunction()

add_executable(tests main.cpp)

target_compile_options(tests PRIVATE 
    $<$<OR:$<STREQUAL:"${CMAKE_CXX_COMPILER_ID}","GNU">,$<STREQUAL:"${CMAKE_CXX_COMPILER_ID}","Clang">>:-g -O0 --coverage -Wall -Wextra -Wno-long-long -pedantic -fsanitize=address -fno-omit-frame-pointer> 
    $<$<STREQUAL:"${CMAKE_CXX_COMPILER_ID}","GNU">:-fdiagnostics-color=always> 
    $<$<STREQUAL:"${CMAKE_CXX_COMPILER_ID}","Clang">:-fcolor-diagnostics> 
)

target_link_options(tests PRIVATE 
    $<$<OR:$<STREQUAL:"${CMAKE_CXX_COMPILER_ID}","GNU">,$<STREQUAL:"${CMAKE_CXX_COMPILER_ID}","Clang">>:--coverage -fsanitize=address -fno-omit-frame-pointer> 
)

target_compile_features(tests PUBLIC
    cxx_std_14
)

target_include_directories(tests
    PUBLIC
    ${GTEST_INCLUDE_DIR}
)

target_link_libraries(tests
    gtest
    mymath
    driver
)

message("coverage enabled")
set(COVERAGE_OPTION 
    $<$<STREQUAL:"${CMAKE_CXX_COMPILER_ID}","Clang">:--gcov-tool>
)

set(COVERAGE_OPTION_PATH
    $<$<STREQUAL:"${CMAKE_CXX_COMPILER_ID}","Clang">:${CMAKE_SOURCE_DIR}/llvm-gcov.sh>
)

add_custom_target(debug_test
    COMMAND lcov -d . -z ${COVERAGE_OPTION} ${COVERAGE_OPTION_PATH}
    COMMAND lcov -c -i -d . -o test_coverage.base ${COVERAGE_OPTION} ${COVERAGE_OPTION_PATH} 
    COMMAND tests
    COMMAND lcov -d . -c -o test_coverage.info  ${COVERAGE_OPTION} ${COVERAGE_OPTION_PATH}  
    COMMAND lcov -a test_coverage.base -a test_coverage.info -o test_coverage.total  ${COVERAGE_OPTION} ${COVERAGE_OPTION_PATH}  
    COMMAND lcov -r test_coverage.total "*gcc*" "*googletest*" "*gtest*" "*/usr/include*" "*mingw*" "*test/*" --output-file ${PROJECT_BINARY_DIR}/test_coverage.info.cleaned  ${COVERAGE_OPTION} ${COVERAGE_OPTION_PATH}  
    COMMAND ${CMAKE_COMMAND} -E rm test_coverage.base test_coverage.total

    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    DEPENDS tests
)

add_custom_target(test_coverage_to_html
    COMMAND genhtml -o test_coverage_to_html --num-spaces 4 -s --legend ${PROJECT_BINARY_DIR}/test_coverage.info.cleaned
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    DEPENDS debug_test
)

add_custom_target(release_test
    COMMAND tests
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    DEPENDS tests
)
