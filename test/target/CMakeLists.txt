project(tests C)

include(ExternalProject)

set(UNITY_BUILD_DIR ${CMAKE_BINARY_DIR}/unity)
set(UNITY_INSTALL_DIR ${CMAKE_SOURCE_DIR}/unity)
set(UNITY_INCLUDE_DIR ${UNITY_INSTALL_DIR}/src)
set(UNITY_LIB_DIR ${UNITY_INSTALL_DIR}/lib)

ExternalProject_Add(unitytest
    URL https://github.com/ThrowTheSwitch/Unity/archive/v2.5.1.tar.gz
    PREFIX ${UNITY_BUILD_DIR}
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    TEST_COMMAND ""
)

ExternalProject_Get_Property(unitytest SOURCE_DIR)

ExternalProject_Add_Step(
    unitytest
    copySource
    WORKING_DIRECTORY ${SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_directory src ${UNITY_INSTALL_DIR}/src
    COMMAND ${CMAKE_COMMAND} -E copy_directory extras/fixture/src ${UNITY_INSTALL_DIR}/src
    COMMAND ${CMAKE_COMMAND} -E copy_directory extras/memory/src ${UNITY_INSTALL_DIR}/src
    COMMENT "Copying extras to ${UNITY_INSTALL_DIR}/extra"
    DEPENDEES download
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

add_executable(tests.elf 
    ${UNITY_INCLUDE_DIR}/unity.c
    ${UNITY_INCLUDE_DIR}/unity_fixture.c
    ${UNITY_INCLUDE_DIR}/unity_memory.c
)

add_subdirectory(test_runners)

target_compile_options(tests.elf PRIVATE
    -Os -mmcu=atmega168pa -Wall -DUNITY_INCLUDE_CONFIG_H
)

target_link_options(tests.elf PRIVATE
    -Os -mmcu=atmega168pa -Wall -DUNITY_INCLUDE_CONFIG_H
)

target_link_libraries(tests.elf
    mymath
    driver
)

target_include_directories(tests.elf
    PRIVATE
    ${UNITY_INCLUDE_DIR}
)

target_compile_features(tests.elf PRIVATE
    c_std_99
)

add_custom_target(debug_test
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    DEPENDS tests.elf
)

add_custom_target(release_test
    COMMAND avr-objcopy -j .text -j .data -O ihex tests.elf tests.hex
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    DEPENDS tests.elf
)

add_unit_test(tests.elf test1)
