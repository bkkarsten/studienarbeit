import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts

import QuickQanava as Qan

Qan.EdgeItem {
    id: customEdge
    // width: 110; height: 60
    // x: 15;      y: 15
    property string edgeLabel: "Default Label"
    Qan.EdgeTemplate {
        anchors.fill: parent
        edgeItem: parent
        color: Material.foreground          // HERE
    }

    // Add a label to the edge
    Label {
        anchors.centerIn: parent
        text: parent.edgeLabel
        color: "black"
        background: Rectangle {
            color:"white"
        }
        font.bold: true
    }
}
