import QtQuick 2.15
import QtQuick.Controls 2.15

// A column that can contain text and image content.
Rectangle {
    property var marginTop: 0
    property var marginBottom: 0
    color: "white"
    height: contentColumn.height + marginTop + marginBottom

    Column {
        id: contentColumn
        objectName: "contentColumn"
        width: parent.width
        Rectangle {
            width: parent.width
            height: marginTop
            color: "transparent"
        }
    }

    // Add a text element to the column.
    function addTextElement(text) {
        var newText = Qt.createQmlObject(
            'import QtQuick 2.15; Text { text: "' + text + '"; wrapMode: Text.Wrap; width: parent.width; horizontalAlignment: Text.AlignHCenter }',
            contentColumn
        );
    }

    // Add an image element to the column.
    function addImageElement(path) {
        var newImage = Qt.createQmlObject(
            'import QtQuick 2.15; Image { source: "file:///' + path + '"; width: parent.width; fillMode: Image.PreserveAspectFit }',
            contentColumn
        );
    }

    // Clear all elements from the column.
    function clearElements() {
        for (var i = contentColumn.children.length - 1; i >= 0; i--) {
            var child = contentColumn.children[i];
            if (child !== contentColumn) {
                child.destroy();
            }
        }
    }

    function setElements(elements, types) {
        clearElements();
        for(var i = 0; i < elements.length; i++) {
            var element = elements[i];
            if(types[i] === "text") {
                addTextElement(element);
            } 
            else if(types[i] === "image") {
                addImageElement(element);
            }
        }
    } 
}