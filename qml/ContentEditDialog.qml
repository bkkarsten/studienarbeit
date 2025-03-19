import QtQuick
import QtQuick.Controls 2.5

import QuickQanava as Qan

Dialog {
    property var contentOwner: null

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
            }
        }
        Button {
            text: "Insert Image"
        }
    }

    onOpened: {
        if (contentOwner) {
            contentTextField.text = contentOwner.contentTextForm;
        }
    }

    onAccepted: {
        if (contentOwner) {
            contentOwner.contentTextForm = contentTextField.text;
        }
    }
}