import QtQuick 2.12
import QtQuick.Layouts 1.12
import "../widgets"

Item {
    id: root

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            Layout.alignment: Qt.AlignTop
            Layout.fillWidth: true
            Layout.margins: 10

            Text {
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                text: dateTimeSource.date
                color: settingsManager.theme.fontColor
                font.pointSize: 22

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        appWindow.showCalendarPage()
                    }
                }
            }

            Item {
                Layout.fillWidth: true
                Layout.fillHeight: true

                LocationWidget {
                    anchors.right: parent.right
                    anchors.top: parent.top

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            appWindow.showTrafficPage()
                        }
                    }
                }
            }
        }

        Text {
            Layout.fillWidth: true
            text: dateTimeSource.time
            color: settingsManager.theme.fontColor
            font.pointSize: 28
            horizontalAlignment: Text.AlignHCenter

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    appWindow.showClockAlarmPage()
                }
            }
        }

        WeatherWidget {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }

    MouseArea {
        anchors.fill: parent
        propagateComposedEvents: true

        onDoubleClicked: {
            appWindow.showSettingsPage()
        }
    }
}
