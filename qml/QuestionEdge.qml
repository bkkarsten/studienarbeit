import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts

import QuickQanava as Qan

// An egde that represents a question and holds Content.
Qan.EdgeItem {
    id: questionEdge
    Qan.EdgeTemplate {
        anchors.fill: parent
        edgeItem: parent
        color: Material.foreground
    }

    Content {
        id: content
        objectName: "content"
        width: 100

        MouseArea {
            anchors.fill: parent
            onDoubleClicked: contentEditDialog.open()
        }
    }

    EdgeMover {
        edgeItem: questionEdge
    }

    onEdgeDoubleClicked: contentEditDialog.open()

    ContentEditDialog {
        id: contentEditDialog
        contentOwner: edge
    }
}
