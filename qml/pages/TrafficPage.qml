import QtQuick 2.12
import QtLocation 5.12
import "../components"

Item {
    id: root

    Map {
        id: map
        anchors.fill: parent
        plugin: Plugin {
            name: "mapboxgl"

            PluginParameter {
                name: "mapboxgl.mapping.use_fbo"
                value: false
            }
        }
        center: locationSource.coordinate
        zoomLevel: 14

        Component.onCompleted: {
            var params = [
                        "country-label-lg", "country-label-md", "country-label-sm",
                        "state-label-lg", "state-label-md", "state-label-sm",
                        "marine-label-lg-pt", "marine-label-lg-ln", "marine-label-md-pt",
                        "marine-label-md-ln", "marine-label-sm-pt", "marine-label-sm-ln",
                        "place-city-lg-n", "place-city-lg-s", "place-city-md-n",
                        "place-city-md-s", "place-city-sm", "place-island", "place-town",
                        "place-village", "place-hamlet", "place-suburb",
                        "place-neighbourhood", "place-islet-archipelago-aboriginal",
                        "airport-label", "poi-scalerank1", "place-residential",
                        "water-label", "water-label-sm","poi-scalerank2",
                        "motorway-junction", "poi-scalerank3", "poi-scalerank4-l1",
                        "poi-scalerank4-l15", "waterway-label"
                    ]
            var lang = settingsManager.language
            lang = lang.substr(0, lang.indexOf('_'));
            // mapboxgl doesn't support Polish language
            if (lang === 'pl') {
                lang = 'en'
            }

            var qml = "import QtLocation 5.12; MapParameter {property var layer; property var textField}"
            for (var j = 0; j < params.length; ++j) {
                var param = Qt.createQmlObject(qml, map)
                param.type = "layout"
                param.layer = params[j]
                param.textField = ["get", "name_" + lang]
                map.addMapParameter(param)
            }

            for (var i = 0; i < map.supportedMapTypes.length; ++i) {
                if (map.supportedMapTypes[i].name === settingsManager.theme.mapStyle) {
                    map.activeMapType = map.supportedMapTypes[i]
                    return
                }
            }
        }

        MapQuickItem {
            id: currentLocation
            sourceItem: Rectangle {
                width: 40
                height: width
                color: settingsManager.theme.locationMarkShadow
                smooth: true
                radius: width / 2

                Rectangle {
                    anchors.centerIn: parent
                    width: 20
                    height: width
                    color: settingsManager.theme.locationMarkColor
                    border.width: 2
                    border.color: settingsManager.theme.locationMarkBorder
                    smooth: true
                    radius: width / 2
                }
            }
            coordinate: locationSource.coordinate
            opacity: 1.0
            anchorPoint: Qt.point(sourceItem.width / 2, sourceItem.height / 2)
        }

        MouseArea {
            anchors.fill: parent
            propagateComposedEvents: true
        }
    }

    Column {
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: appWindow.height / 40
        anchors.rightMargin: appWindow.height / 40
        spacing: appWindow.height / 80

        IconButton {
            height: appWindow.height / 20
            anchors.horizontalCenter: parent.horizontalCenter
            source: "qrc:/resources/gps.svg"
            color: settingsManager.theme.mapControlColor
            onClicked: map.alignCoordinateToPoint(locationSource.coordinate,
                                                  Qt.point(root.width / 2, root.height / 2))
        }

        IconButton {
            height: appWindow.height / 20
            anchors.horizontalCenter: parent.horizontalCenter
            source: "qrc:/resources/plus.svg"
            color: settingsManager.theme.mapControlColor
            onClicked: map.zoomLevel++
        }

        IconButton {
            height: appWindow.height / 20
            anchors.horizontalCenter: parent.horizontalCenter
            source: "qrc:/resources/minus.svg"
            color: settingsManager.theme.mapControlColor
            onClicked: map.zoomLevel--
        }
    }
}
