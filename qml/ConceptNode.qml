import QtQuick
import QtQuick.Layouts
import QtQuick.Effects
import QtQuick.Controls.Material

import QuickQanava as Qan

// A node that holds Content.
Qan.NodeItem {
    id: conceptNode
    width:60
    height:60

    CustomRectNodeTemplate {
        anchors.fill: parent
        nodeItem : parent
        id: template
    }

    Content {
        id: content
        objectName: "content"
        width: 0.9 * conceptNode.width
        anchors.centerIn: parent
    }

    onNodeDoubleClicked: contentEditDialog.open()

    ContentEditDialog {
        id: contentEditDialog
        contentOwner: node
    }
}
