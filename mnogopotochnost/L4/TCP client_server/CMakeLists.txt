cmake_minimum_required(VERSION 3.15)
project(TCPProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Для Windows подключаем библиотеку ws2_32
if(WIN32)
    set(PLATFORM_LIBS ws2_32)
endif()

# Создаём исполняемый файл для клиента
add_executable(tcp_client client.cpp)
target_link_libraries(tcp_client PRIVATE ${PLATFORM_LIBS})

# Создаём исполняемый файл для сервера
add_executable(tcp_server server.cpp)
target_link_libraries(tcp_server PRIVATE ${PLATFORM_LIBS})
