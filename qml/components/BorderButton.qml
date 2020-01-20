import QtQuick 2.12
import QtQuick.Controls 2.12

Button {
    id: root

    property real minimumPointSize: 12
    property int fontSizeMode: Text.VerticalFit

    font.pointSize: 30

    contentItem: Text {
        text: root.text
        font.pointSize: root.font.pointSize
        minimumPointSize: root.minimumPointSize
        fontSizeMode: root.fontSizeMode
        color: settingsManager.theme.fontColor
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    background: Rectangle {
        anchors.fill: parent
        color: "transparent"
        border.color: settingsManager.theme.fontColor
        border.width: 2
        radius: 10
    }
}
