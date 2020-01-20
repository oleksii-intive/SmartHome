import QtQuick 2.12
import "../components"

Column {
    id: root
    spacing: height / 20
    topPadding: height * 2 / 20
    bottomPadding: height * 2 / 20

    property string time
    property string icon
    property int temperature

    Text {
        width: parent.width
        height: parent.height * 4 / 20
        text: root.time
        color: settingsManager.theme.fontColor
        fontSizeMode: Text.VerticalFit
        minimumPointSize: 20
        font.pointSize: 50
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignBottom
    }

    ColorIcon {
        height: parent.height * 7 / 20
        anchors.horizontalCenter: parent.horizontalCenter
        source: root.icon
        color: settingsManager.theme.smallIconColor
    }

    Text {
        width: parent.width
        height: parent.height * 4 / 20
        text: root.temperature + "\u00B0"
        color: settingsManager.theme.fontColor
        fontSizeMode: Text.VerticalFit
        minimumPointSize: 20
        font.pointSize: 50
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignTop
    }
}
