import QtQuick 2.12
import QtQuick.Layouts 1.12
import "../components"

Item {
    id: root

    property date time: new Date()

    height: appWindow.height / 5

    GridLayout {
        anchors.horizontalCenter: parent.horizontalCenter
        columns: 3
        rows: 3
        columnSpacing: 0
        rowSpacing: 0

        IconButton {
            Layout.alignment: Qt.AlignHCenter
            source: "qrc:/resources/up.svg"
            color: settingsManager.theme.popupIconColor
            height: appWindow.height / 20

            onClicked: {
                time = new Date(time.setHours(time.getHours() + 1))
            }
        }

        IconButton {
            Layout.alignment: Qt.AlignHCenter
            Layout.column: 2
            source: "qrc:/resources/up.svg"
            color: settingsManager.theme.popupIconColor
            height: appWindow.height / 20

            onClicked: {
                if (time.getMinutes() == 59) {
                    time = new Date(time.setMinutes(0))
                } else {
                    time = new Date(time.setMinutes(time.getMinutes() + 1))
                }
            }
        }

        Text {
            text: Qt.formatTime(time, "HH")
            height: appWindow.height / 10
            fontSizeMode: Text.VerticalFit
            minimumPointSize: 20
            font.pointSize: 60
            color: settingsManager.theme.popupFontColor
        }

        Text {
            text: ":"
            height: appWindow.height / 10
            fontSizeMode: Text.VerticalFit
            minimumPointSize: 20
            font.pointSize: 60
            color: settingsManager.theme.popupFontColor
        }

        Text {
            text: Qt.formatTime(time, "mm")
            height: appWindow.height / 10
            fontSizeMode: Text.VerticalFit
            minimumPointSize: 20
            font.pointSize: 60
            color: settingsManager.theme.popupFontColor
        }

        IconButton {
            Layout.alignment: Qt.AlignHCenter
            source: "qrc:/resources/down.svg"
            color: settingsManager.theme.popupIconColor
            height: appWindow.height / 20

            onClicked: {
                time = new Date(time.setHours(time.getHours() - 1))
            }
        }

        IconButton {
            Layout.alignment: Qt.AlignHCenter
            Layout.column: 2
            Layout.row: 2
            source: "qrc:/resources/down.svg"
            color: settingsManager.theme.popupIconColor
            height: appWindow.height / 20

            onClicked: {
                if (time.getMinutes() == 0) {
                    time = new Date(time.setMinutes(59))
                } else {
                    time = new Date(time.setMinutes(time.getMinutes() - 1))
                }
            }
        }
    }
}
