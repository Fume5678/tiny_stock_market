cmake_minimum_required(VERSION 3.14)

set(this asio_learn)
project(${this})

set(ROOT_PATH ${PROJECT_SOURCE_DIR})

add_subdirectory(client)
add_subdirectory(server)
#add_subdirectory(tests)