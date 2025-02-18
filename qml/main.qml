import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: "Studienarbeit"

    menuBar: MenuBar {
        Menu {
            title: "File"
            Action { text: "New" }
            Action { text: "Open" }
            Action { text: "Save" }
            Action { text: "Save As" }
        }
        Action {
            text: "Review"
        }
    }


    property var content: null

    Rectangle {
        width: parent.width
        height: parent.height
        color:"lightgray"

        Loader {
            anchors.fill: parent
            sourceComponent: content
        }
    }
}