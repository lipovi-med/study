cmake_minimum_required(VERSION 3.19)
project(L2 LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

qt_add_executable(L2
    main.cpp
)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Network
    Sql
)

target_link_libraries(L2
    PRIVATE
        Qt6::Core
        Qt6::Network
        Qt6::Sql
)

include(GNUInstallDirs)

install(TARGETS L2
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
