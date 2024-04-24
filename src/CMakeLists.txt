cmake_minimum_required(VERSION 3.5)

project(Wallet VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)


set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.hpp
        mainwindow.ui
        dialog.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Wallet
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        dialog.hpp dialog.cpp

        MoneySystem.hpp

        addaccount.hpp addaccount.cpp addaccount.ui




        registrationsystem.hpp registrationsystem.cpp registrationsystem.ui
        loginsystem.hpp loginsystem.cpp loginsystem.ui
        deleteaccountconfirm.hpp deleteaccountconfirm.cpp deleteaccountconfirm.ui
        MoneySystem.cpp


    )

else()
    if(ANDROID)
        add_library(Wallet SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Wallet
            ${PROJECT_SOURCES}
        )
    endif()
endif()


target_include_directories(Wallet PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(Wallet PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(Wallet PRIVATE Qt${QT_VERSION_MAJOR}::Sql)


if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Wallet)
endif()
set_target_properties(Wallet PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Wallet
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Wallet)
endif()
