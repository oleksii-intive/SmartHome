import QtQuick 2.12

ColorIcon {
    id: root

    signal clicked()

    MouseArea {
        anchors.fill: parent
        onClicked: {
            root.clicked()
        }
    }
}
