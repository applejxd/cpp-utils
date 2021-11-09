#find_package(GTest REQUIRED)

enable_testing()

add_executable(${CMAKE_PROJECT_NAME} main_test.cpp)
target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC
        # 最適化
        -mtune=native -march=native -mfpmath=both -O2
        # 各種警告
        -Wall -Wextra -Wshadow -Wconversion -Wfloat-equal -Wno-char-subscripts
        # 数値関連エラー：オーバーフロー・未定義動作を検出
        -ftrapv -fno-sanitize-recover
        )
target_compile_features(${CMAKE_PROJECT_NAME} PUBLIC cxx_std_11)
target_link_libraries(${CMAKE_PROJECT_NAME}
        gtest gtest_main pthread
        glog::glog)

#include(GoogleTest)
#gtest_discover_tests(main_test)