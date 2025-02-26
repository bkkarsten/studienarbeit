import QtQuick 2.15
import QtQuick.Controls 2.15
import QuickQanava as Qan
import "qrc:/QuickQanava" as Qan

Qan.GraphView {
    anchors.fill: parent
    grid : null
    graph: Qan.Graph {
        id: graph
        objectName: "graph"
        anchors.fill: parent
    }
}