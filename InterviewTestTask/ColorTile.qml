import QtQuick 2.13

Rectangle {
    id: gridView
    required property Item dragParent
    signal pressed
    signal released
    signal clicked

    property int visualIndex: 0

    anchors {
        horizontalCenter: parent.horizontalCenter
        verticalCenter: parent.verticalCenter
    }
    radius: 10

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        drag.target: gridView
        onClicked: gridView.clicked()
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
        }
    ]
}
