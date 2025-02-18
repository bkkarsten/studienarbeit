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
            Action { 
                text: "New" 
                onTriggered: window.newFile()
            }
            Action { 
                text: "Open" 
                onTriggered: window.openFile()
            }
            Action { 
                text: "Save" 
                onTriggered: window.saveFile()
            }
            Action { 
                text: "Save As" 
                onTriggered: window.saveFileAs()
            }
        }
        Menu {
            title: "Review"
        }
    }

    Rectangle {
        width: parent.width
        height: parent.height

        Loader {
            id: loader
            objectName: "loader"
            anchors.fill: parent
            source: "qrc:/no_file.qml"
        }
    }
}