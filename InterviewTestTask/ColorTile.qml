import QtQuick 2.13
import QtQuick.Controls 2.13

Rectangle {
    id: gridView
    required property Item dragParent
    required property var colorDialogId
    required property color selectedColor
    signal pressed
    signal released
    signal clicked

    property int visualIndex: 0

    color: selectedColor
    anchors {
        horizontalCenter: parent.horizontalCenter
        verticalCenter: parent.verticalCenter
    }
    radius: 10

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        drag.target: gridView
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: (mouse) => {
            if (mouse.button === Qt.LeftButton)
            {
                gridView.clicked()
            }
            else
            {
                console.log("right click")
                colorDialogId.colorTileVisualIndex = visualIndex
                colorDialogId.open()
            }
        }
        onPressed: gridView.pressed()
        onReleased: {
            parent.Drag.drop()
            gridView.released()
        }
    }

    Drag.active: mouseArea.drag.active
    Drag.source: gridView
    Drag.hotSpot.x: gridView.width / 2
    Drag.hotSpot.y: gridView.height / 2

    states: [
        State {
            when: mouseArea.drag.active
            ParentChange {
                target: gridView
                parent: gridView.dragParent
            }

            AnchorChanges {
                target: gridView
                anchors.horizontalCenter: undefined
                anchors.verticalCenter: undefined
            }

            PropertyChanges {
                target: gridView;
                scale: 0.5
                z: 10
            }
        }
    ]

    Behavior on x {
        enabled: mouseArea.drag.active
        NumberAnimation { duration: 10; easing.type: Easing.OutBack }
    }

    Behavior on y {
        enabled: mouseArea.drag.active
        NumberAnimation { duration: 10; easing.type: Easing.OutBack }
    }

    transitions: Transition { NumberAnimation { property: "scale"; duration: 100 } }
}
