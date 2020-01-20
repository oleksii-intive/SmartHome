import QtQuick 2.12
import "../components"

Item {
    width: row.width
    height: row.height

    Row {
        id: row
        Text {
            id: text
            text: locationSource.location
            color: settingsManager.theme.fontColor
            font.pointSize: 22
            wrapMode: Text.WordWrap
        }

        ColorIcon {
            height: text.height
            source: "qrc:/resources/location.svg"
            color: settingsManager.theme.iconColor
        }
    }
}
