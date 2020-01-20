import QtQuick 2.12
import QtQuick.Controls 2.12

CheckBox {
    id: root

    property bool popup: false

    indicator: Rectangle {
        implicitWidth: 26
        implicitHeight: 26
        x: root.leftPadding
        y: parent.height / 2 - height / 2
        color: root.popup
               ? settingsManager.theme.popupControlBg
               : settingsManager.theme.controlBg
        border {
            color: root.popup
                   ? settingsManager.theme.popupControlColor
                   : settingsManager.theme.controlColor
            width: 2
        }

        Text {
            anchors.centerIn: parent
            visible: root.checked
            color: root.popup
                   ? settingsManager.theme.popupControlColor
                   : settingsManager.theme.controlColor
            text: "\u2713"
            fontSizeMode: Text.VerticalFit
            minimumPointSize: 12
            font.pointSize: 30
        }
    }

    contentItem: Text {
        text: root.text
        font: root.font
        opacity: enabled ? 1.0 : 0.3
        color: root.popup
               ? settingsManager.theme.popupFontColor
               : settingsManager.theme.fontColor
        verticalAlignment: Text.AlignVCenter
        leftPadding: root.indicator.width + root.spacing
    }
}
