import QtQuick
import QtQuick.Layouts
import QtQuick.Effects
import QtQuick.Controls.Material

import QuickQanava as Qan

Qan.NodeItem {
    id: conceptNode
    width:60
    height:60

    Rectangle {
        id: background
        z: 1
        anchors.fill: parent
        radius: 2
        color: "white"
        border.color: "black"
        border.width: 2

        Content {
            id: content
            objectName: "content"
        }
    }
}
