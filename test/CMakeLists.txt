cmake_minimum_required(VERSION 3.16)

# cf. https://google.github.io/googletest/quickstart-cmake.html
find_package(GTest REQUIRED)
find_package(glog 0.5.0 REQUIRED)
find_package(Boost REQUIRED)

enable_testing()

file(GLOB path_list *.cpp)
foreach (path ${path_list})
    get_filename_component(target_name ${path} NAME_WE)
    add_executable(${target_name} ${path})
    target_compile_options(${target_name} PUBLIC
            # 各種警告
            -Wall -Wextra -Wshadow -Wconversion -Wfloat-equal -Wno-char-subscripts
            # 数値関連エラー：オーバーフロー・未定義動作を検出
            -ftrapv -fno-sanitize-recover
            # デバッグ情報付与
            $<$<CONFIG:Debug>: -g>
            # 最適化
            $<$<CONFIG:Release>: -mtune=native -march=native -mfpmath=both -O2>
            )
    target_compile_features(${target_name} PUBLIC cxx_std_14)

    target_include_directories(${target_name} PUBLIC
            ${PROJECT_SOURCE_DIR}/include)
    target_link_libraries(${target_name}
            glog::glog
            pthread
            gtest gtest_main)

    gtest_discover_tests(${target_name})
endforeach ()