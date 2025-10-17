#минимальная версия cmake
cmake_minimum_required(VERSION 3.10)
#имя проекта
project(T2)
#добавляем поддиректорию, в которой будет catch2
add_subdirectory(catch2)
#добавляем цель - приложение, у которого исходник с единственным приложением
add_executable(T2 main.cpp)
#линкуемся к catch2, в котором уже есть main
target_link_libraries(T2 PRIVATE Catch2::Catch2 Catch2::Catch2WithMain)