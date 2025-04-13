import QtQuick 2.15
import QtQuick.Controls 2.15
import QtMultimedia

Item {
    id: resultScreen
    objectName: "resultScreen"

    anchors.fill: parent

    property int reachedScore: 0
    property int totalScore: 0
    property var numAnswers: [] // amount of answers rated at the quality correspondign to the index

    Button {
        id: exitButton
        text: "Exit"
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 10
        onClicked: {
            manager.exitReview();
        }
    }

    Column {
        anchors.centerIn: parent
        spacing: 20

        Text {
            text: "Congratulations, you completed today's review!"
            font.pixelSize: 24
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter
            color: "darkgreen"
        }

        Text {
            text: "Score: " + reachedScore + " / " + totalScore
            font.pixelSize: 20
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true

                Text {
                    id: hoverText
                    text: numAnswers.map((num, index) => num > 0 ? `${num} question${num>1?"s":""} with ${index} point${index>1?"s":""}${num>1?" each":""}\n` : "").join("")
                    font.pixelSize: 16
                    color: "gray"
                    visible: false
                    anchors.top: parent.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                onEntered: hoverText.visible = true
                onExited: hoverText.visible = false
            }
        }
    }

    SoundEffect {
        id: fanfare
        source: "qrc:/sounds/fanfare.wav"
    }

    onVisibleChanged: {
        if(visible) {
            fanfare.play();
        }
    }
}