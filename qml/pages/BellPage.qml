import QtQuick 2.12
import "../components"

Rectangle {
    id: root

    color: settingsManager.theme.semitransparentBg

    ColorIcon {
        id: bellIcon
        anchors.centerIn: parent
        height: appWindow.height / 2
        source: "qrc:/resources/bell.svg"
        color: settingsManager.theme.iconColor

        SequentialAnimation {
            running: root.visible
            loops: Animation.Infinite
            ScaleAnimator {
                target: bellIcon
                from: 0.5
                to: 1.5
                duration: 1000
            }
            ScaleAnimator {
                target: bellIcon
                from: 1.5
                to: 0.5
                duration: 1000
            }
        }
    }

    MouseArea {
        anchors.fill: parent

        onClicked: {
            alarmManager.stopAlarm()
        }
    }
}
