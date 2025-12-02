cmake_minimum_required(VERSION 3.16)
project(ascii_video_player LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

add_executable(ascii_video_player ascii_video_player.cpp)
target_link_libraries(ascii_video_player PRIVATE ${OpenCV_LIBS})
