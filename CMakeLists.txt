cmake_minimum_required(VERSION 3.16)
project(StudienArbeit LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
# set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_BUILD_TYPE Release)

find_package(Qt6 REQUIRED COMPONENTS Qml Quick Core Gui Widgets)

#qt_add_resources(QRC_FILES resources.qrc)

set(SOURCES
    main.cpp
)

add_executable(studar ${SOURCES})

add_subdirectory(external/QuickQanava)
target_include_directories(studar  PUBLIC QuickQanava Qt6::QuickControls2)

target_sources(studar PRIVATE ${QRC_FILES})
target_link_libraries(studar PRIVATE QuickQanava QuickQanavaplugin Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick Qt6::Widgets)
