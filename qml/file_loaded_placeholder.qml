import QtQuick
import QtQuick.Controls

Rectangle {
    width: parent.width
    height: parent.height
    color: "lightgray"

    Button {
        anchors.centerIn: parent
        text: "Make Changes"
        onClicked: window.registerChanges()
    }

    // Text {
    //     text: "Graph opened. WIP!"
    //     anchors.centerIn: parent
    // }
}
