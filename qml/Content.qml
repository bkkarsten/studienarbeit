import QtQuick 2.15
import QtQuick.Controls 2.15

// A column that can contain text and image content.
Column {
    id: contentColumn
    objectName: "contentColumn"
    anchors.fill: parent

    // Add a text element to the column.
    function addTextElement(text) {
        var newText = Qt.createQmlObject(
            'import QtQuick 2.15; Text { text: "' + text + '"; wrapMode: Text.Wrap }',
            contentColumn
        );
    }

    // Add an image element to the column.
    function addImageElement(path) {
        var newImage = Qt.createQmlObject(
            'import QtQuick 2.15; Image { source: "' + path + '"; width: parent.width; fillMode: Image.PreserveAspectFit }',
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

    // Example usage
    Component.onCompleted: {
        addTextElement("Hello, dynamic text!");
        addImageElement("file:///c:/users/bkars/a.png");
    }
}
