import QtQuick 2.15
import QtQuick.Controls 2.15
import QuickQanava as Qan
import "qrc:/QuickQanava" as Qan
import studar 1.0

Qan.GraphView {
    anchors.fill: parent
    grid : null
    graph: KnowledgeGraph {
        id: graph
        objectName: "graph"
        anchors.fill: parent
    }
}