cmake_minimum_required(VERSION 3.5)

project(HostsBlocker VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

set(PROJECT_SOURCES
        main.cpp
        hostblocker.cpp
        hostblocker.h
        hostblocker.ui
        ${CMAKE_CURRENT_SOURCE_DIR}/resources.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(HostsBlocker
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${QT_RESOURCES}
    )
else()
    if(ANDROID)
        add_library(HostsBlocker SHARED
            ${PROJECT_SOURCES}
            ${QT_RESOURCES}
        )
    else()
        add_executable(HostsBlocker
            ${PROJECT_SOURCES}
            ${QT_RESOURCES}
        )
    endif()
endif()

target_link_libraries(HostsBlocker PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network)

set_target_properties(HostsBlocker PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS HostsBlocker
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(HostsBlocker)
endif()
