import QtQuick
import QtCore
import QtQuick.Controls 2.5
import QtQuick.Dialogs

import QuickQanava as Qan

Dialog {
    property var contentOwner: null
    property bool editCustomWeight: false

    id: contentEditDialog
    title: "Edit Content"
    standardButtons: Dialog.Ok | Dialog.Cancel

    Column {
        id: dialogBody
        spacing: 10
        width: parent.width
        ScrollView {
            width: parent.width
            height: 100
            TextArea {
                id: contentTextField
                focus: true
                wrapMode: TextEdit.Wrap
                color: "black"
                background: Rectangle {
                    color: "white"
                }

                Keys.onPressed: (event) => {
                    if ((event.key === Qt.Key_Enter || event.key === Qt.Key_Return) && event.modifiers & Qt.ControlModifier) {
                        contentEditDialog.accept();
                    }
                }
            }
        }
        Button {
            text: "Insert Image"
            onClicked: fileDialog.open()
        }
        Label {
            text: "Question weight: " + customWeightSlider.expValue.toFixed(2)
            visible: editCustomWeight
        }
        ExponentialSlider {
            id: customWeightSlider
            visible: editCustomWeight
            min: 0.1
            max: 10
        }
    }

    onOpened: {
        if (contentOwner) {
            contentTextField.text = contentOwner.contentTextForm;
            if(editCustomWeight) {
                customWeightSlider.setExpValue(contentOwner.customWeight);
            }
        }
    }

    onAccepted: {
        if (contentOwner) {
            contentOwner.contentTextForm = contentTextField.text;
            if (editCustomWeight) {
                contentOwner.customWeight = customWeightSlider.expValue;
            }
        }
    }

    FileDialog {
        id: fileDialog
        title: "Choose an image"
        currentFolder: StandardPaths.writableLocation(StandardPaths.PicturesLocation)
        nameFilters: ["Image files (*.png *.jpg *.bmp)", "All files (*)"]
        onAccepted: {
            let path = fileDialog.selectedFile.toString();
            path = path.replace(/^(file:\/{3})/,"");
            contentTextField.insert(contentTextField.cursorPosition, "img(" + path + ")");
        }
    }
}