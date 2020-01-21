import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import "../components"
import  "../widgets"

Item {
    id: root

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10

        Text {
            Layout.alignment: Qt.AlignHCenter
            text: dateTimeSource.date + " " + dateTimeSource.time
            color: settingsManager.theme.fontColor
            font.pointSize: 22
        }

        ListView {
            id: alarmsList
            Layout.fillHeight: true
            Layout.fillWidth: true
            clip: true
            model: alarmManager.alarms
            delegate: Item {
                width: parent.width
                height: appWindow.height / 8

                GridLayout {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.right: parent.right
                    columns: 2
                    rowSpacing: 0

                    Text {
                        text: Qt.formatTime(modelData.time, "HH:mm")
                        Layout.preferredHeight: appWindow.height * 3 / 40
                        color: settingsManager.theme.fontColor
                        fontSizeMode: Text.VerticalFit
                        minimumPointSize: 12
                        font.pointSize: 30
                    }

                    Switch {
                        id: switchWidget

                        Layout.rowSpan: 2
                        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter

                        implicitHeight: appWindow.height * 3 / 40
                        implicitWidth: implicitHeight * 2
                        checked: modelData.active

                        indicator: Rectangle {
                            implicitWidth: implicitHeight * 2
                            implicitHeight: parent.height * 3 / 4
                            x: switchWidget.leftPadding
                            y: parent.height / 2 - height / 2
                            radius: implicitHeight / 2
                            color: switchWidget.checked ? "#a8172d" : "#ffffff"
                            border.color: switchWidget.checked ? "#a8172d" : "#cccccc"

                            Rectangle {
                                x: switchWidget.checked ? parent.width - width : 0
                                width: parent.implicitHeight
                                height: parent.implicitHeight
                                radius: parent.implicitHeight / 2
                                color: switchWidget.down ? "#cccccc" : "#ffffff"
                                border.color: switchWidget.checked ? "#a8172d" : "#999999"
                            }
                        }

                        MouseArea {
                            anchors.fill: parent

                            onClicked: {
                                modelData.active = !modelData.active
                                alarmManager.processActiveChanged(alarmsList.currentIndex)
                            }
                        }
                    }

                    Text {
                        text: qsTr("Repeat: %1").arg(modelData.repeatAsString)
                        Layout.preferredHeight: appWindow.height / 40
                        Layout.maximumWidth: parent.width - switchWidget.width
                        color: settingsManager.theme.fontColor
                        fontSizeMode: Text.VerticalFit
                        minimumPointSize: 10
                        font.pointSize: 20
                    }
                }

                Rectangle {
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    height: 1
                    width: parent.width
                    color: settingsManager.theme.separatorColor
                }

                MouseArea {
                    anchors.fill: parent
                    propagateComposedEvents: true

                    onClicked: {
                        var point = mapToItem(switchWidget, mouse.x, mouse.y)
                        if (switchWidget.contains(point)) {
                            mouse.accepted = false
                        } else {
                            alarmsList.currentIndex = index
                        }
                    }

                    onDoubleClicked: {
                        darknerLoader.active = true
                    }
                }
            }

            highlight: Component {
                Rectangle {
                    width: alarmsList.width
                    height: appWindow.height / 10
                    color: settingsManager.theme.highlightColor
                }
            }

            MouseArea {
                anchors.fill: parent
                propagateComposedEvents: true
            }
        }

        IconButton {
            height: appWindow.height / 20
            Layout.alignment: Qt.AlignHCenter
            source: "qrc:/resources/plus.svg"
            color: settingsManager.theme.iconColor

            onClicked: {
                alarmManager.addNewAlarm()
                alarmsList.currentIndex = alarmManager.alarms.length - 1
                darknerLoader.active = true
            }
        }
    }

    Loader {
        id: darknerLoader

        anchors.fill: parent
        active: false
        sourceComponent: Component {
            Rectangle {
                anchors.fill: parent
                color: "#80000000"

                AlarmWidget {
                    id: alarmWidget
                    anchors.centerIn: parent
                    alarmData: alarmManager.alarms[alarmsList.currentIndex]
                    onDeleteAlarm: {
                        darknerLoader.active = false
                        alarmManager.deleteAlarm(alarmsList.currentIndex)
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    propagateComposedEvents: true

                    onClicked: {
                        var point = mapToItem(alarmWidget, mouse.x, mouse.y)
                        if (alarmWidget.contains(point)) {
                            mouse.accepted = false
                        } else {
                            darknerLoader.active = false
                            alarmManager.saveAlarmChanges(alarmsList.currentIndex)
                        }
                    }
                }
            }
        }
    }
}
