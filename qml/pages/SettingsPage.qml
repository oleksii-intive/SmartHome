import QtQuick 2.12
import "../components"

Item {
    Grid {
        anchors.centerIn: parent
        columns: 2
        columnSpacing: appWindow.width / 40
        rowSpacing: appWindow.height / 40

        Text {
            height: appWindow.height / 15
            text: qsTr("Language")
            color: settingsManager.theme.fontColor
            font.pointSize: 22
            verticalAlignment: Text.AlignVCenter
        }

        ComboBox {
            height: appWindow.height / 15
            currentIndex: settingsManager.languageIndex()
            textRole: "name"
            model: settingsManager.languages

            onCurrentIndexChanged: {
                settingsManager.updateLanguage(currentIndex)
            }
        }

        Text {
            height: appWindow.height / 15
            text: qsTr("Wallpaper")
            color: settingsManager.theme.fontColor
            font.pointSize: 22
            verticalAlignment: Text.AlignVCenter
        }

        ComboBox {
            height: appWindow.height / 15
            currentIndex: settingsManager.wallpaperIndex()
            textRole: "name"
            model: settingsManager.wallpapers

            onCurrentIndexChanged: {
                settingsManager.updateWallpaper(currentIndex)
            }
        }

        Text {
            height: appWindow.height / 15
            text: qsTr("Theme")
            color: settingsManager.theme.fontColor
            font.pointSize: 22
            verticalAlignment: Text.AlignVCenter
        }

        ComboBox {
            height: appWindow.height / 15
            currentIndex: settingsManager.themeIndex()
            model: settingsManager.themes

            onCurrentIndexChanged: {
                settingsManager.updateTheme(currentIndex)
            }
        }
    }

    Component.onDestruction: {
        settingsManager.saveChanges()
    }
}
