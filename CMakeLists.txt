cmake_minimum_required(VERSION 3.27.1)

add_compile_options(-std=c++17 -stdlib=libc++)

project(proj)

# add_executable(${PROJECT_NAME} main.cpp)
add_executable(client c.cpp)
add_executable(server s.cpp)

# target_include_directories(
#     ${PROJECT_NAME}
#     PUBLIC ${PROJECT_SOURCE_DIR}/asio-1.18.0/include
# )

target_include_directories(
    client
    PUBLIC ${PROJECT_SOURCE_DIR}/asio-1.18.0/include
)

target_include_directories(
    server
    PUBLIC ${PROJECT_SOURCE_DIR}/asio-1.18.0/include
)