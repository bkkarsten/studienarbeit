import QtQuick

/**
 * Simple QML content that informs the user that no graph (file) has been opened yet.
 */
Rectangle {
    width: parent.width
    height: parent.height
    color: "lightgray"

    Text {
        text: "No graph opened. Click File->New or File->Open to start!"
        anchors.centerIn: parent
    }
}
