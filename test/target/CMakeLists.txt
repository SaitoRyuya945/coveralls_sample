project(tests C)

include(ExternalProject)

# UnityTestをビルドするディレクトリを指定
set(UNITY_BUILD_DIR ${CMAKE_BINARY_DIR}/unity)
set(UNITY_INSTALL_DIR ${CMAKE_SOURCE_DIR}/unity)
set(UNITY_INCLUDE_DIR ${UNITY_INSTALL_DIR}/include)
set(UNITY_LIB_DIR ${UNITY_INSTALL_DIR}/lib)

ExternalProject_Add(unitytest
    URL https://github.com/ThrowTheSwitch/Unity/archive/v2.5.1.zip
    PREFIX ${UNITY_BUILD_DIR}
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${UNITY_INSTALL_DIR} -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
)

add_library(unity IMPORTED STATIC GLOBAL)
set_target_properties(unity PROPERTIES
    IMPORTED_LOCATION ${UNITY_LIB_DIR}/libunity.a
)

function(add_unit_test target_name name)
    target_sources(${target_name}
        PRIVATE
        ${name}.c
    )
    add_test(
        NAME ${name}
        COMMAND ${name}
    )
endfunction()

add_executable(tests)

add_subdirectory(test_runners)

target_compile_options(tests PRIVATE
    -Os -mmcu=attiny2313 -Wall
)

target_include_directories(tests
    PUBLIC
    ${UNITY_INCLUDE_DIR}
)

target_link_libraries(tests
    unity
    mymathlib
)

add_custom_target(release_test
    #COMMAND tests
    COMMAND echo "HELLO"
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    #DEPENDS tests
)

add_unit_test(tests test1)
