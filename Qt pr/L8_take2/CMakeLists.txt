cmake_minimum_required(VERSION 3.19)
project(L8_take2 LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Sql Concurrent)

qt_standard_project_setup()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

qt_add_executable(L8_take2
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    database.h database.cpp
    dbdata.h dbdata.cpp dbdata.ui
    PG_Libs/libcrypto-3-x64.dll PG_Libs/libiconv-2.dll PG_Libs/libintl-9.dll PG_Libs/libpq.dll PG_Libs/libssl-3-x64.dll
)

target_link_libraries(L8_take2
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Sql
        Qt::Concurrent
)

include(GNUInstallDirs)

install(TARGETS L8_take2
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET L8_take2
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
