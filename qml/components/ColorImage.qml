import QtQuick 2.12
import QtGraphicalEffects 1.12

Item {
    id: root

    property url source
    property color color

    Image {
        id: image
        anchors.fill: parent
        source: root.source
    }

    ColorOverlay {
        anchors.fill: image
        source: image
        color: root.color
    }
}
