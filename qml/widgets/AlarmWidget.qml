import QtQuick 2.12
import QtQuick.Layouts 1.12
import "../components" as Components

Rectangle {
    id: root

    property var alarmData

    signal deleteAlarm()

    implicitWidth: appWindow.width * 4 / 5
    implicitHeight: clockEdit.height + checkBox.height + repeatRow.height
                    + daysRow.height + deleteButton.height + 4 * columnLayout.spacing + 2 * 10
    color: settingsManager.theme.popupBg
    border.color: settingsManager.theme.popupBorder
    border.width: 2

    QtObject {
        id: _private

        readonly property Text weekdaysText: Text {
            width: (root.width - 2 * 10) / 3
            text: qsTr("Weekdays")
            fontSizeMode: Text.HorizontalFit
            minimumPointSize: 18
            font.pointSize: 36
        }
        readonly property Text mondayText: Text {
            width: (root.width - 6 * 10) / 7
            text: qsTr("Mon")
            fontSizeMode: Text.HorizontalFit
            minimumPointSize: 12
            font.pointSize: 24
        }

        readonly property real repeatFontSize: weekdaysText.fontInfo.pointSize
        readonly property real dayFontSize: mondayText.fontInfo.pointSize
    }

    ColumnLayout {
        id: columnLayout
        anchors.fill: parent
        anchors.margins: 10

        ClockEdit {
            id: clockEdit
            Layout.fillWidth: true
            time: alarmData.time
        }

        Components.CheckBox {
            id: checkBox
            text: qsTr("Repeat")
            checked: alarmData.repeat
            font.pointSize: 22
            popup: true

            onCheckedChanged: {
                if (!checked) {
                    monText.checked = false
                    tueText.checked = false
                    wedText.checked = false
                    thuText.checked = false
                    friText.checked = false
                    satText.checked = false
                    sunText.checked = false
                    alarmData.repeat = false
                } else if (!alarmData.repeat) {
                    monText.checked = true
                    tueText.checked = true
                    wedText.checked = true
                    thuText.checked = true
                    friText.checked = true
                    satText.checked = true
                    sunText.checked = true
                }
            }

            MouseArea {
                anchors.fill: parent

                onClicked: {
                    checkBox.checked = !checkBox.checked
                }
            }
        }

        Row {
            id: repeatRow

            Layout.fillWidth: true

            spacing: 10
            enabled: checkBox.checked

            Components.ClickableText {
                checked: parent.enabled
                checkable: false
                text: qsTr("Weekdays")
                font.pointSize: _private.repeatFontSize
                popup: true

                onClicked: {
                    monText.checked = true
                    tueText.checked = true
                    wedText.checked = true
                    thuText.checked = true
                    friText.checked = true
                    satText.checked = false
                    sunText.checked = false
                }
            }

            Components.ClickableText {
                checked: parent.enabled
                checkable: false
                text: qsTr("Weekend")
                font.pointSize: _private.repeatFontSize
                popup: true

                onClicked: {
                    monText.checked = false
                    tueText.checked = false
                    wedText.checked = false
                    thuText.checked = false
                    friText.checked = false
                    satText.checked = true
                    sunText.checked = true
                }
            }

            Components.ClickableText {
                checked: parent.enabled
                checkable: false
                text: qsTr("Everyday")
                font.pointSize: _private.repeatFontSize
                popup: true

                onClicked: {
                    monText.checked = true
                    tueText.checked = true
                    wedText.checked = true
                    thuText.checked = true
                    friText.checked = true
                    satText.checked = true
                    sunText.checked = true
                }
            }
        }

        Row {
            id: daysRow

            Layout.fillWidth: true

            spacing: 10
            enabled: checkBox.checked

            function testAllDays() {
                if (!monText.checked && !tueText.checked && !wedText.checked && !thuText.checked
                        && !friText.checked && !satText.checked && !sunText.checked) {
                    checkBox.checked = false
                }
            }

            function checkedDays() {
                var days = []
                if (monText.checked) {
                    days.push(1)
                }
                if (tueText.checked) {
                    days.push(2)
                }
                if (wedText.checked) {
                    days.push(3)
                }
                if (thuText.checked) {
                    days.push(4)
                }
                if (friText.checked) {
                    days.push(5)
                }
                if (satText.checked) {
                    days.push(6)
                }
                if (sunText.checked) {
                    days.push(7)
                }
                return days
            }

            Components.ClickableText {
                id: monText
                text: qsTr("Mon")
                font.pointSize: _private.dayFontSize
                checked: alarmData.days.includes(1)
                popup: true

                onClicked: {
                    daysRow.testAllDays()
                }
            }

            Components.ClickableText {
                id: tueText
                text: qsTr("Tue")
                font.pointSize: _private.dayFontSize
                checked: alarmData.days.includes(2)
                popup: true

                onClicked: {
                    daysRow.testAllDays()
                }
            }

            Components.ClickableText {
                id: wedText
                text: qsTr("Wed")
                font.pointSize: _private.dayFontSize
                checked: alarmData.days.includes(3)
                popup: true

                onClicked: {
                    daysRow.testAllDays()
                }
            }

            Components.ClickableText {
                id: thuText
                text: qsTr("Thu")
                font.pointSize: _private.dayFontSize
                checked: alarmData.days.includes(4)
                popup: true

                onClicked: {
                    daysRow.testAllDays()
                }
            }

            Components.ClickableText {
                id: friText
                text: qsTr("Fri")
                font.pointSize: _private.dayFontSize
                checked: alarmData.days.includes(5)
                popup: true

                onClicked: {
                    daysRow.testAllDays()
                }
            }

            Components.ClickableText {
                id: satText
                text: qsTr("Sat")
                font.pointSize: _private.dayFontSize
                checked: alarmData.days.includes(6)
                popup: true

                onClicked: {
                    daysRow.testAllDays()
                }
            }

            Components.ClickableText {
                id: sunText
                text: qsTr("Sun")
                font.pointSize: _private.dayFontSize
                checked: alarmData.days.includes(7)
                popup: true

                onClicked: {
                    daysRow.testAllDays()
                }
            }
        }

        Components.IconButton {
            id: deleteButton
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter
            source: "qrc:/resources/delete.svg"
            color: settingsManager.theme.popupIconColor
            height: appWindow.height / 20

            onClicked: {
                root.deleteAlarm()
            }
        }
    }

    Component.onDestruction: {
        alarmData.time = clockEdit.time
        alarmData.repeat = checkBox.checked
        if (alarmData.repeat) {
            alarmData.days = daysRow.checkedDays()
        } else {
            alarmData.days = []
        }
    }
}
