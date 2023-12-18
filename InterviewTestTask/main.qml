import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Window 2.13
import QtQml.Models 2.13
import ColorModels 1.0

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
            console.log("Function errorDialog.error called: " + t)
            errorDialog.open()
        }

        Component.onCompleted:{
            console.log("Connect the client")
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

        property var elemCount

        onRejected:{
            console.log("Cancel button pressed")
            client.stop()
        }

        function startDownload(num) {
            progressBarId.to = num
            elemCount = num
            console.log("Start downloading")
            downloadDialog.open()
        }

        function finishDownload() {
            console.log("Stop downloading")
            downloadDialog.close()
        }

        function newElement(el) {
            console.log("On new element -> " + el)
            progressBarId.value = el

            if (el === elemCount)
                downloadDialog.close()
        }

        Component.onCompleted:{
            client.startDownload.connect(startDownload)
            client.finishDownload.connect(finishDownload)
            client.elementDownloaded.connect(newElement)
        }

        ProgressBar {
            id: progressBarId
            from: 0
            value: 0
            anchors.horizontalCenter: parent.horizontalCenter
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

        onAccepted: {
            console.log("onAccepted")

        }

        Component.onCompleted:{
            console.log("colorDialog: onCompleted")
            //client.
        }
    }

    GridView {
        id: gridView
        width: parent.width
        height: parent.height

        cellWidth: 100
        cellHeight: 100

        displaced: Transition {
            NumberAnimation {
                properties: "x,y"
                easing.type: Easing.OutQuad
            }
        }

        model: DelegateModel {
            id: visualModel
            model: ColorModel.listOfColorItems

            // each square is both a drag-able item as well as a droparea (to drop items in).
            delegate: DropArea {
                id: delegateRoot
                required property color color
                property int modelIndex

                width: gridView.cellWidth
                height: gridView.cellHeight

                onEntered: function (drag) {
                    var from = (drag.source as ColorTile).visualIndex
                    var to = colorTile.visualIndex
                    visualModel.items.move(from, to)
                }

                onDropped: function (drag) {
                    var from = modelIndex
                    var to = (drag.source as ColorTile).visualIndex
                    ColorModel.listOfColorItems.move(from, to)
                }

                property int visualIndex: DelegateModel.itemsIndex

                ColorTile {
                    id: colorTile
                    width: gridView.cellWidth * 0.95
                    height: gridView.cellHeight * 0.95
                    dragParent: gridView
                    colorDialogId: colorDialog
                    visualIndex: delegateRoot.visualIndex
                    selectedColor: delegateRoot.color
                    onPressed: delegateRoot.modelIndex = visualIndex
                }
            }
        }
    }
}
