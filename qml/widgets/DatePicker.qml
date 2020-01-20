import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Rectangle {
    id: root

    property date selectedDate

    implicitWidth: _private.dayWidth + _private.monthWidth
                   + _private.yearWidth + 2 * tumblersLayout.spacing + 30
    implicitHeight: appWindow.height * 2 / 3
    color: settingsManager.theme.popupBg
    border.color: settingsManager.theme.popupBorder
    border.width: 2

    QtObject {
        id: _private

        readonly property int startYear: 1970
        readonly property int endYear: 2050
        property var yearModel: []
        property var dayModel: []

        readonly property TextMetrics textMetricsDay: TextMetrics {
            font.family: tumbler.font.family
            font.bold: true
            font.pointSize: 30
            text: "31"
        }
        readonly property TextMetrics textMetricsMonth: TextMetrics {
            font.family: monthTumbler.font.family
            font.bold: true
            font.pointSize: 30
            text: "September"
        }
        readonly property TextMetrics textMetricsYear: TextMetrics {
            font.family: yearTumbler.font.family
            font.bold: true
            font.pointSize: 30
            text: "2020"
        }
        readonly property int defaultMargin: 5
        readonly property real dayWidth: textMetricsDay.advanceWidth + 2 * defaultMargin
        readonly property real monthWidth: textMetricsMonth.advanceWidth + 2 * defaultMargin
        readonly property real yearWidth: textMetricsYear.advanceWidth + 2 * defaultMargin

        function initYearModel() {
            var start = _private.startYear
            var end = _private.endYear
            _private.yearModel = []
            while (end >= start) {
                _private.yearModel.push(end--)
            }
            _private.yearModelChanged()
            yearTumbler.positionViewAtIndex(_private.endYear - new Date().getFullYear(), Tumbler.Center)
        }

        function getDayModel(month, year) {
            var start = 1
            var end = daysInMonth(month, year)
            var dayModel = []
            while (end >= start) {
                dayModel.push(start++)
            }
            return dayModel
        }

        function daysInMonth (month, year) {
            return new Date(year, month + 1, 0).getDate();
        }

        Component.onCompleted: {
            initYearModel()
        }
    }

    RowLayout {
        id: tumblersLayout

        anchors.fill: parent
        spacing: 10

        Tumbler {
            id: tumbler
            Layout.preferredHeight: root.height
            Layout.preferredWidth: _private.dayWidth
            model: _private.getDayModel(monthTumbler.currentIndex,
                                        _private.endYear - yearTumbler.currentIndex)
            currentIndex: selectedDate.getDate() - 1
            delegate: Text {
                text: modelData
                font.bold: Tumbler.displacement == 0
                font.pointSize: Tumbler.displacement == 0 ? 30 : 25
                color: settingsManager.theme.popupFontColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                opacity: 1.0 - Math.abs(Tumbler.displacement) / (tumbler.visibleItemCount / 2)
            }

            onCurrentIndexChanged: {
                if (!root.visible) return
                if (yearTumbler.model.length === 0) return
                selectedDate = new Date(_private.endYear - yearTumbler.currentIndex,
                                        monthTumbler.currentIndex,
                                        currentIndex + 1)
            }
        }

        Tumbler {
            id: monthTumbler
            Layout.preferredHeight: root.height
            Layout.preferredWidth: _private.monthWidth
            model: [
               qsTr("January"),
               qsTr("February"),
               qsTr("March"),
               qsTr("April"),
               qsTr("May"),
               qsTr("June"),
               qsTr("July"),
               qsTr("August"),
               qsTr("September"),
               qsTr("October"),
               qsTr("November"),
               qsTr("December")
            ]
            currentIndex: selectedDate.getMonth()
            delegate: Text {
                text: modelData
                font.bold: Tumbler.displacement == 0
                font.pointSize: Tumbler.displacement == 0 ? 30 : 25
                color: settingsManager.theme.popupFontColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                opacity: 1.0 - Math.abs(Tumbler.displacement) / (tumbler.visibleItemCount / 2)
            }
            onCurrentIndexChanged: {
                if (!root.visible) return
                if (yearTumbler.model.length === 0) return
                selectedDate = new Date(_private.endYear - yearTumbler.currentIndex,
                                        currentIndex,
                                        tumbler.currentIndex + 1)
            }
        }

        Tumbler {
            id: yearTumbler
            Layout.preferredWidth: _private.yearWidth
            Layout.preferredHeight: root.height
            model: _private.yearModel
            currentIndex: _private.endYear - selectedDate.getFullYear()
            delegate: Text {
                text: modelData
                font.bold: Tumbler.displacement == 0
                font.pointSize: Tumbler.displacement == 0 ? 30 : 25
                color: settingsManager.theme.popupFontColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                opacity: 1.0 - Math.abs(Tumbler.displacement) / (tumbler.visibleItemCount / 2)
            }
            onCurrentIndexChanged: {
                if (!root.visible) return
                selectedDate = new Date(_private.endYear - currentIndex,
                                        monthTumbler.currentIndex,
                                        tumbler.currentIndex + 1)
            }
        }
    }
}
