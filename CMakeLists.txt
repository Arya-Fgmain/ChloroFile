cmake_minimum_required(VERSION 3.27.1)

add_compile_options(-std=c++11 -stdlib=libc++)

project(proj)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/asio-1.18.0/include
)
