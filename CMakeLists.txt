cmake_minimum_required(VERSION 3.14)
project(TreesPresentation)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_library(library ${RCC_SOURCES} ${SOURCES})
find_package(Qt5Core)
SET(TreesPresentation_RESOURCES resources.qrc)
QT5_ADD_RESOURCES(TreesPresentation_RESOURCES_RCC ${TreesPresentation_RESOURCES})

add_executable(TreesPresentation
        mainwindow.cpp
        main.cpp
        AVLTree.cpp
        SplayTree.cpp
        RBTree.cpp
        VertexList.cpp
        ${TreesPresentation_RESOURCES_RCC})

target_link_libraries(TreesPresentation Qt5::Widgets)
