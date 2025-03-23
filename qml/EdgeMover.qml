import QtQuick 2.15
import QtQml

// When added to an edge item, allows the user to drag that edge to new nodes the destination or source of the edge.
Item {
    property var edgeItem: null
    property var boxSize: 20

    anchors.fill: parent
    
    DraggableRect {
        id: rect1
        width: boxSize
        height: boxSize
        color: rect1.dragged ? Qt.rgba(0, 0, 163, 0.5) : "transparent"
        defaultX: edgeItem.p1.x - boxSize / 2
        defaultY: edgeItem.p1.y - boxSize / 2
        onRelease: function(target) {
            edgeItem.edge.changeSource(target);
        }
    }

    DraggableRect {
        id: rect2
        width: boxSize
        height: boxSize
        color: rect2.dragged ? Qt.rgba(0, 0, 163, 0.5) : "transparent"
        defaultX: edgeItem.p2.x - boxSize / 2
        defaultY: edgeItem.p2.y - boxSize / 2
        onRelease: function(target) {
            edgeItem.edge.changeDestination(target);
        }
    }

    
}