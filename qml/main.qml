import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12
import "pages"
import "components"

ApplicationWindow {
    id: appWindow
    visibility: Window.FullScreen
    background: ColorImage {
        source: settingsManager.wallpaper
        color: settingsManager.theme.overlayBg
    }

    function showHomePage() {
        stackView.pop(null)
    }

    function showSettingsPage() {
        stackView.push(settingsComponent)
    }

    function showTrafficPage() {
        stackView.push(trafficComponent)
    }

    function showCalendarPage() {
        stackView.push(calendarComponent)
    }

    function showAlarmPage() {
        stackView.push(alarmComponent)
    }

    StackView {
        id: stackView
        anchors.fill: parent

        initialItem: HomePage {}

        MouseArea {
            anchors.fill: parent

            onPressAndHold: {
                appWindow.showHomePage()
            }
        }
    }

    Component {
        id: settingsComponent

        SettingsPage {}
    }

    Component {
        id: trafficComponent

        TrafficPage {}
    }

    Component {
        id: calendarComponent

        CalendarPage {}
    }

    Component {
        id: alarmComponent

        AlarmPage {}
    }

    Component {
        id: bellComponent

        BellPage {}
    }

    Connections {
        target: alarmManager
        onTimeForAlarm: {
            stackView.push(bellComponent)
        }
        onTimeToStopAlarm: {
            stackView.pop()
        }
    }
}
