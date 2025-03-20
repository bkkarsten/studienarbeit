cmake_minimum_required(VERSION 3.16)
project(StudienArbeit LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_BUILD_TYPE Debug)

find_package(Qt6 REQUIRED COMPONENTS Qml Quick Core Gui Widgets)

set(BOOST_LIBRARYDIR "${BOOST_ROOT}/stage/lib")

find_package(Boost 1.87 REQUIRED)  

qt_add_resources(QRC_FILES qml/resources.qrc)

set(SOURCES
    main.cpp
    src/WindowManager.cpp
    src/initialiseDirectory.cpp
    src/Content.cpp
    src/ConceptNode.cpp
    src/QuestionEdge.cpp
    src/RelationNode.cpp
    src/ConnectorEdge.cpp
    src/Question.cpp
    src/NodeBase.cpp
    src/EdgeBase.cpp
    src/KnowledgeGraph.cpp
    src/KeyboardHelper.cpp
)

add_executable(studar ${SOURCES})

add_subdirectory(external/QuickQanava)
target_include_directories(studar PUBLIC 
    .
    ./src
    QuickQanava 
    Qt6::QuickControls2
    ${Boost_INCLUDE_DIRS}
)

target_sources(studar PRIVATE ${QRC_FILES})
target_link_libraries(studar PRIVATE QuickQanava QuickQanavaplugin Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick Qt6::Widgets)

qt_policy(SET QTP0001 NEW)
# qt_add_qml_module(studar
#     URI studar
#     VERSION 1.0
#     SOURCES src/KnowledgeGraph.hpp src/KnowledgeGraph.cpp src/KeyboardHelper.hpp
# )
