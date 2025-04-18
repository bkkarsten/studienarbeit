import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: reviewUI
    objectName: "reviewUI"
    property int numButtons: 0
    property var buttonTexts: []
    property var buttonColours: []

    property int numContexts: 0
    property int numAnswers: 0

    property bool revealed: false
    property bool reverse: false

    property int totalQuestions: 0
    property int currentQuestion: 1

    anchors.fill: parent

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
        anchors.fill: parent
        spacing: 20

        Rectangle {
            width: parent.width
            height: 40
            color: "transparent"

            Text {
                anchors.centerIn: parent
                text: `Question ${currentQuestion} / ${totalQuestions}`
            }
        }

        Row {
            width: parent.width - 50
            height: parent.height - 140
            anchors.horizontalCenter: parent.horizontalCenter

            Switcher {
                width: parent.width / 3
                height: parent.height
                show: +(!revealed && reverse)

                ScrollView {
                    anchors.fill: parent
                    contentWidth: availableWidth
                    Column {
                        width: parent.width
                        spacing: 10
                        Repeater {
                            objectName: "contextContents"
                            model: numContexts
                            Content {
                                width: parent.width
                                marginTop: 9
                                marginBottom: 6
                                border.width: 2
                            }
                            
                        }
                    }
                }
                
                Rectangle {
                    width: parent.width
                    height: 75
                    color: "lightgray"
                    Text {
                        anchors.centerIn: parent
                        text: `Click to reveal ${numContexts} answer${numContexts > 1 ? "s" : ""}`
                        color: "black"
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: revealed = true
                    }
                }
            }

            Column {
                width: parent.width / 3
                height: parent.height

                Canvas {
                    width: parent.width
                    height: 30
                    
                    onPaint: {
                        var ctx = getContext("2d");
                        ctx.reset();
                        ctx.clearRect(0, 0, width, height);
                        ctx.moveTo(width * 0.1, height * 0.5);
                        ctx.lineTo(width * 0.9, height * 0.5);
                        ctx.lineTo(width * 0.9 - 10, height * 0.5 + 10);
                        ctx.moveTo(width * 0.9, height * 0.5);
                        ctx.lineTo(width * 0.9 - 10, height * 0.5 - 10);
                        ctx.stroke();
                    }
                }

                Content {
                    objectName: "questionContent"
                    width: parent.width * 0.7
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }

            Switcher {
                width: parent.width / 3
                height: parent.height
                show: +(!revealed && !reverse)
                ScrollView {
                    anchors.fill: parent
                    contentWidth: availableWidth
                    Column {
                        width: parent.width
                        spacing: 10
                        Repeater {
                            objectName: "answerContents"
                            model: numAnswers
                            Content {
                                width: parent.width
                                marginTop: 9
                                marginBottom: 6
                                border.width: 2
                            }
                        }
                    }
                }
                Rectangle {
                    width: parent.width
                    height: 75
                    color: "lightgray"
                    Text {
                        anchors.centerIn: parent
                        text: `Click to reveal ${numAnswers} answer${numAnswers > 1 ? "s" : ""}`
                        color: "black"
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: revealed = true
                    }
                }
            }
        }

        Row {
            id: buttonRow
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10
            visible: revealed
            Repeater {
                
                model: numButtons
                Button {
                    width: Math.min(
                        reviewUI.width / numButtons - buttonRow.spacing,
                        parent.children.reduce((maxWidth, child) => Math.max(maxWidth, child.implicitWidth), 0)
                    )
                    height: parent.children.reduce((maxHeight, child) => Math.max(maxHeight, child.implicitHeight), 0)
                    palette.button: buttonColours[index]
                    contentItem: Text {
                        text: buttonTexts[index]
                        color: "white"
                        wrapMode: Text.WordWrap
                        clip: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }

                    onClicked: {
                        manager.answerQuestion(index);
                    }
                }
            }
        }
    }
}