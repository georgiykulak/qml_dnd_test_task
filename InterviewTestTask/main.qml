import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Window 2.13
import QtQml.Models 2.13


ApplicationWindow {
    id: application

    width: 720
    height: 480

    title: "Client App"
    visible: true

    Rectangle {
        color: "#242424"
        anchors.fill: parent
    }

    Dialog {
        id: errorDialog
        title: "Error..."
        modal: true

        standardButtons: Dialog.Ok
        x: (parent.width - width) / 2
        y: (parent.height - height) / 2

        onAccepted: {
            console.log("And of course you could only agree.")
            Qt.quit()
        }

        function error(t) {
        }

        Component.onCompleted:{
            client.errorSignal.connect(error)
        }
    }

    Dialog {
        id: downloadDialog
        modal: true
        standardButtons: Dialog.Cancel
        x: (parent.width - width) / 2
        y: (parent.height - height) / 2
        title: "Downloading..."

        onRejected:{
            client.stop()
        }

        function startDownload(num) {

        }
        function finishDownload() {

        }

        function newElement(el) {
        }

        Component.onCompleted:{
            client.startDownload.connect(startDownload)
            client.finishDownload.connect(finishDownload)
            client.elementDownloaded.connect(newElement)
            client.run()
        }
    }

    Dialog {
        id: colorDialog
        title: "Enter new color"
        modal: true
        standardButtons: Dialog.Cancel | Dialog.Ok

        x: (parent.width - width) / 2
        y: (parent.height - height) / 2
        focus: true

        TextInput {
            id: inputText
            text: "color"
            cursorVisible: true
            focus: true
            anchors.fill: parent
            Keys.onReturnPressed: colorDialog.accept()
        }

        onAccepted:{
        }
    }

    GridView {
        id: gridView

        cellWidth: 100
        cellHeight: 100

        anchors.fill: parent

        model: DelegateModel {
            id: visualModel
            model: client.model
        }
    }
}
