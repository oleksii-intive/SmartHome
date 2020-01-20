import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qt.labs.calendar 1.0
import "../components"
import "../widgets"

Item {
    id: root

    property date selectedDate: new Date()

    onSelectedDateChanged: {
        grid.month = root.selectedDate.getMonth()
        grid.year = root.selectedDate.getFullYear()
    }

    QtObject {
        id: _private

        readonly property TextMetrics monthTextMetrics: TextMetrics {
            font.family: monthText.font.family
            font.pointSize: monthText.fontInfo.pointSize
            text: "September"
        }

        readonly property real monthTextWidth: monthTextMetrics.advanceWidth
    }

    Column {
        id: column
        anchors.fill: parent
        anchors.margins: 5
        spacing: appWindow.height / 80

        Item {
            height: appWindow.height / 20
            width: parent.width

            Text {
                id: dateText
                anchors.left: parent.left
                anchors.right: monthRow.left
                height: parent.height
                text: dateTimeSource.date
                color: settingsManager.theme.fontColor
                verticalAlignment: Text.AlignVCenter
                fontSizeMode: Text.Fit
                minimumPointSize: 12
                font.pointSize: 30
            }

            Row {
                id: monthRow
                anchors.horizontalCenter: parent.horizontalCenter
                height: parent.height

                IconButton {
                    color: settingsManager.theme.iconColor
                    source: "qrc:/resources/prev.svg"
                    height: appWindow.height / 20

                    onClicked: {
                        var date = root.selectedDate
                        root.selectedDate = new Date(date.setMonth(date.getMonth() - 1))
                    }
                }

                Text {
                    id: monthText
                    width: _private.monthTextWidth
                    height: appWindow.height / 20
                    color: settingsManager.theme.fontColor
                    minimumPointSize: 12
                    font.pointSize: 30
                    fontSizeMode: Text.VerticalFit
                    text: grid.locale.monthName(root.selectedDate.getMonth(),
                                                Locale.LongFormat)
                    horizontalAlignment: Text.AlignHCenter
                }

                IconButton {
                    color: settingsManager.theme.iconColor
                    source: "qrc:/resources/next.svg"
                    height: appWindow.height / 20

                    onClicked: {
                        var date = root.selectedDate
                        root.selectedDate = new Date(date.setMonth(date.getMonth() + 1))
                    }
                }
            }

            BorderButton {
                width: dateText.contentWidth
                anchors.right: parent.right
                height: parent.height
                text: qsTr("Select")

                onClicked: {
                    darknerLoader.active = true
                }
            }
        }

        ColumnLayout {
            id: layout
            height: appWindow.height - 5 * appWindow.height / 80 - 10
            width: parent.width

            DayOfWeekRow {
                id: dayWeekRow
                locale: grid.locale
                delegate: Text {
                    text: model.shortName
                    font: dayWeekRow.font
                    color: settingsManager.theme.fontColor
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                Layout.fillWidth: true
            }

            MonthGrid {
                id: grid
                locale: Qt.locale(settingsManager.language)
                spacing: 1
                delegate: Label {
                    leftPadding: 10
                    topPadding: 10
                    opacity: model.month === grid.month ? 1 : 0.75
                    text: model.day
                    font: grid.font
                    color: settingsManager.theme.popupFontColor
                    background: Rectangle {
                        function getColor(date) {
                            if (model.today)
                                return settingsManager.theme.todayBg
                            if (model.day === date.getDate() && model.month === date.getMonth())
                                return settingsManager.theme.selectedBg
                            return settingsManager.theme.itemBg
                        }

                        color: getColor(root.selectedDate)
                        opacity: model.month === grid.month ? 1 : 0.75
                    }
                }

                Layout.fillWidth: true
                Layout.fillHeight: true

                onClicked: {
                    root.selectedDate = date
                }

                onPressAndHold: {
                    appWindow.showHomePage()
                }
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

                DatePicker {
                    id: datePicker
                    anchors.centerIn: parent
                    selectedDate: root.selectedDate

                    onSelectedDateChanged: {
                        root.selectedDate = datePicker.selectedDate
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    propagateComposedEvents: true

                    onPressed: {
                        var point = mapToItem(datePicker, mouse.x, mouse.y)
                        if (datePicker.contains(point)) {
                            mouse.accepted = false
                        } else {
                            darknerLoader.active = false
                        }
                    }
                }
            }
        }
    }
}
