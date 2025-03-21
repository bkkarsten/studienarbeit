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

    Qan.RectNodeTemplate {
        anchors.fill: parent
        nodeItem : parent
        id: template
    }

    Content {
        id: content
        objectName: "content"
        width: 0.9 * conceptNode.width
    }
}
