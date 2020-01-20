import QtQuick 2.12

Text {
    id: root

    property bool checked: false
    property bool checkable: true
    property bool popup: false

    signal clicked()

    color: checked ? _private.color : _private.checkedColor

    QtObject {
        id: _private

        readonly property color color: root.popup
                                       ? settingsManager.theme.popupFontColor
                                       : settingsManager.theme.fontColor
        readonly property color checkedColor: root.popup
                                              ? settingsManager.theme.popupCheckedFontColor
                                              : settingsManager.theme.checkedFontColor
    }

    MouseArea {
        anchors.fill: parent

        onClicked: {
            if (root.checkable) {
                root.checked = !root.checked
            }
            root.clicked()
        }
    }
}
