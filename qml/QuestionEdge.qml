import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts

import QuickQanava as Qan

// An egde that represents a question and holds Content.
Qan.EdgeItem {
    id: customEdge
    Qan.EdgeTemplate {
        anchors.fill: parent
        edgeItem: parent
        color: Material.foreground
    }

    Content {
        id: content
        objectName: "content"
    }
}
