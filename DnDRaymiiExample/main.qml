/* Author: Remy van Elst, https://raymii.org
 * License: GNU AGPLv3
 */

import QtQuick 2.15
import QtQuick.Layouts 1.12
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import org.raymii.ThingModel 1.0

import "./" as Example

Window {
    width: 800
    height: 800
    visible: true
    title: qsTr("Drag & Drop")

    Text {
        id: infoText
        anchors.top: parent.top
        anchors.left: parent.left
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignTop
        color: "black"
        anchors.margins: 5
        fontSizeMode: Text.Fit
        minimumPixelSize: 10
        font.pixelSize: 30
        height: 40
        text: "Drag and drop images below to reorder them"
    }

    Button {
        anchors.top: infoText.bottom
        anchors.left: parent.left
        anchors.leftMargin: 5
        id: printButton
        text: "Log C++ Model"
        onClicked: {
            modeltext.text = ThingModel.printModel()
        }
    }
    Text {
        id: modeltext
        anchors.top: printButton.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 5
        text: ""
        font.pixelSize: 20
        height: 40
        fontSizeMode: Text.Fit
        wrapMode: Text.WordWrap
        minimumPixelSize: 10
    }

    Example.ThingGrid {
        id: g
        anchors.top: modeltext.bottom
        anchors.margins: 5
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }
}
