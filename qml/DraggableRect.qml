import QtQuick

// A rectangle that can be dragged and returns to its default position once no longer dragged.

Rectangle {
    property var defaultX
    property var defaultY
    readonly property bool dragged: dragArea1.drag.active
    property var onDrag
    property var onRelease

    id: rect
    x: defaultX
    y: defaultY
    z: -10
    Drag.active: dragArea1.drag.active
    Drag.hotSpot.x: rect.width / 2
    Drag.hotSpot.y: rect.height / 2

    MouseArea {
        id: dragArea1
        anchors.fill: parent
        z: parent.z
        drag.target: parent

        onReleased: {
            if(typeof rect.onRelease === "function") {
                onRelease(rect.Drag.target);
            }
            parent.x = Qt.binding(function() { return defaultX; });
            parent.y = Qt.binding(function() { return defaultY; });
        }

        onPositionChanged: {
            if(typeof rect.onDrag === "function") {
                onDrag(parent.x, parent.y);
            }
        }
    }
}