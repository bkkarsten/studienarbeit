import QtQuick 2.15
import QtQuick.Controls 2.15
import QuickQanava as Qan
import "qrc:/QuickQanava" as Qan
import studar 1.0

Qan.GraphView {
    id: graphView
    objectName: "graphView"
    anchors.fill: parent
    grid : null
    graph: KnowledgeGraph {
        id: graph
        objectName: "graph"
        anchors.fill: parent
    }
    
    Component.onCompleted: {
        originCross.visible = false;
    }

    property int clickCount: 0
    property int doubleClickInterval: 200 // Time interval in milliseconds

    Timer {
        id: clickTimer
        interval: doubleClickInterval
        repeat: false
        onTriggered: {
            if (clickCount == 1) {
                // Handle single click event
            }
            clickCount = 0
        }
    }

    onClicked: (pos) => {
        clickCount += 1
        if (clickCount == 1) {
            clickTimer.start()
        } else if (clickCount == 2) {
            clickTimer.stop()
            viewDoubleClicked(pos.x - containerItem.x, pos.y - containerItem.y)
            clickCount = 0
        }
    }

    function viewDoubleClicked(x, y) {
        if(KeyboardHelper.modifiers() & Qt.ShiftModifier) {
            graph.insertRelationNode("", x, y);
        }
        else {
            graph.insertConceptNode("", x, y);
        }
    }

    Keys.onPressed: (event) => {
        if (event.key === Qt.Key_Delete || event.key === Qt.Key_Backspace) {
            graph.removeSelection();
            event.accepted = true;
        }
    }
}