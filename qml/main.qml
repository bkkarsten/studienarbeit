import QtQuick 2.15
import QtQuick.Controls 2.15

/**
 * The main application window. It includes a menu bar and a loader which loads content from another 
 * QML file depending on the applications context.
 */
ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: ""

    onClosing: (event) => event.accepted = manager.checkClose();

    menuBar: MenuBar {
        Menu {
            title: "File"
            Action { 
                text: "New" 
                onTriggered: manager.newFile()
            }
            Action { 
                text: "Open" 
                onTriggered: manager.openFile()
            }
            Action { 
                text: "Save" 
                onTriggered: manager.saveFile()
            }
            Action { 
                text: "Save As" 
                onTriggered: manager.saveFileAs()
            }
            Action {
                text: "Close"
                onTriggered: manager.closeFile()
            }
        }
        Menu {
            title: "Review"
            Action {
                text: "Classic"
            }
            Action {
                text: "Graph based"
            }
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