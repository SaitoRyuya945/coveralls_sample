cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_EXTENSIONS OFF)

project(converalls_sample CXX)

include(ExternalProject)

# GoogleTestをビルドするディレクトリを指定
set(GTEST_BUILD_DIR ${CMAKE_BINARY_DIR}/gtest)
# GoogleTestをインストールするディレクトリを指定
set(GTEST_INSTALL_DIR ${PROJECT_SOURCE_DIR}/gtest)
# GoogleTestのヘッダファイルがあるディレクトリ
set(GTEST_INCLUDE_DIR ${GTEST_INSTALL_DIR}/include)
# GoogleTestの静的ライブラリがあるフォルダ
set(GTEST_LIB_DIR ${GTEST_INSTALL_DIR}/lib)

# GoogleTestはpthreadが必要
find_package(Threads REQUIRED)

# GoogleTestを外部プロジェクトとして追加
ExternalProject_Add(googletest
    # ダウンロードするURLを指定
    URL https://github.com/google/googletest/archive/release-1.8.1.zip
    # ビルドするディレクトリを指定
    PREFIX ${GTEST_BUILD_DIR}
    # GoogleTestをダウンロードして回答した後、
    # cmakeを実行するときに渡される引数
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${GTEST_INSTALL_DIR}
)

# gtestを静的ライブラリとして登録
add_library(gtest IMPORTED STATIC GLOBAL)
# gtestに対応する静的ライブラリのファイルと
# その依存ライブラリpthreadを指定
set_target_properties(gtest PROPERTIES
    IMPORTED_LOCATION ${GTEST_LIB_DIR}/libgtest.a
    INTERFACE_LINK_LIBRARIES ${CMAKE_THREAD_LIBS_INIT}
)

# gmockを静的ライブラリとして登録
add_library(gmock IMPORTED STATIC GLOBAL)
# gtestに対応する静的ライブラリのファイルと
# その依存ライブラリpthreadを指定
set_target_properties(gmock PROPERTIES
    IMPORTED_LOCATION ${GTEST_LIB_DIR}/libgmock.a
    INTERFACE_LINK_LIBRARIES ${CMAKE_THREAD_LIBS_INIT}
)

add_library(mymathlib)
target_include_directories(mymathlib
    PUBLIC 
    include/mymath
)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(cli)

enable_testing()
add_subdirectory(test)

add_custom_target(ci
    DEPENDS
        run_mymath_sample
        $<$<CONFIG:Debug>:test_coverage>
        $<$<NOT:$<CONFIG:Debug>>:run_test>
)
