import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts

import QuickQanava as Qan

// An edge that connects a concept node and a relation node. 
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
