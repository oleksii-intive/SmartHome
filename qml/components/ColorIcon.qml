import QtQuick 2.0
import QtGraphicalEffects 1.12

Item {
    id: root

    property color color
    property url source

    width: image.width

    Image {
        id: image

        anchors.horizontalCenter: parent.horizontalCenter
        height: parent.height
        fillMode: Image.PreserveAspectFit
        source: root.source
    }

    ColorOverlay {
        anchors.fill: image
        source: image
        color: root.color
    }
}
