import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts

import QuickQanava as Qan

Qan.EdgeItem {
    id: connectorEdge
    Qan.EdgeTemplate {
        anchors.fill: parent
        edgeItem: parent
        color: Material.foreground
    }

    EdgeMover {
        edgeItem: parent
    }
}
