cmake_minimum_required(VERSION 3.9)

add_executable(csv_battle csv_battle.cpp
)
target_include_directories(csv_battle PUBLIC ../single_include)
target_link_libraries(csv_battle csv)