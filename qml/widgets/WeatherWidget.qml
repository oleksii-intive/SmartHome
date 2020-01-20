import QtQuick 2.12
import QtQuick.Layouts 1.12
import "../components"

Column {
    id: root

    Item {
        height: appWindow.height / 5
        width: image.width * 2.7
        anchors.left: parent.left
        anchors.leftMargin: (appWindow.width - image.width * 2.7) / 2
        anchors.right: parent.right
        anchors.rightMargin: (appWindow.width - image.width * 2.7) / 2

        ColorIcon {
            id: image
            height: parent.height
            source: weatherSource.weatherInfo.icon
            color: settingsManager.theme.iconColor
        }

        Text {
            height: parent.height
            width: image.width
            anchors.right: parent.right
            text: weatherSource.weatherInfo.temperature.toFixed(0) + "\u00B0"
            color: settingsManager.theme.fontColor
            padding: 0
            fontSizeMode: Text.VerticalFit
            minimumPointSize: 40
            font.pointSize: 200
            horizontalAlignment: Text.AlignRight
        }
    }

    Item {
        height: appWindow.height / 20
        width: parent.width
    }

    Text {
        height: appWindow.height / 20
        width: parent.width
        text: qsTr("Humidity:%1%2% Wind:%3%4m/s Pressure:%5%6hPa")
                .arg("\u00A0")
                .arg(weatherSource.weatherInfo.humidity)
                .arg("\u00A0")
                .arg(weatherSource.weatherInfo.windSpeed.toFixed(1))
                .arg("\u00A0")
                .arg(weatherSource.weatherInfo.pressure.toFixed(0))
        color: settingsManager.theme.fontColor
        fontSizeMode: Text.VerticalFit
        minimumPointSize: 20
        font.pointSize: 40
        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.WordWrap
    }

    Item {
        height: appWindow.height / 20
        width: parent.width
    }

    Rectangle {
        width: parent.width
        height: appWindow.height / 4
        color: settingsManager.theme.semitransparentBg

        Row {
            anchors.fill: parent

            Repeater {
                model: weatherSource.weatherForecast
                HourWeatherWidget {
                    time: weather.time
                    temperature: weather.temperature
                    icon: weather.icon
                    width: parent.width / 5
                    height: parent.height
                }
            }
        }
    }
}
