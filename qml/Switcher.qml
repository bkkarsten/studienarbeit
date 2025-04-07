import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: switchComponent
    property int show: 0

    default property alias children: contentItem.data

    Item {
        id: contentItem
        anchors.fill: parent

        Component.onCompleted: {
            for (var i = 0; i < contentItem.children.length; i++) {
                contentItem.children[i].visible = (i === show);
            }
        }

        onChildrenChanged: {
            for (var i = 0; i < contentItem.children.length; i++) {
                contentItem.children[i].visible = (i === show);
            }
        }
    }
    onShowChanged: {
        for (var i = 0; i < contentItem.children.length; i++) {
            contentItem.children[i].visible = (i === show);
        }
    }
}