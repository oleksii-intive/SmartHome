import QtQuick 2.12
import QtQuick.Controls 2.12

ComboBox {
    id: root

    delegate: ItemDelegate {
        width: root.width
        contentItem: Text {
            text: root.textRole
                  ? (Array.isArray(root.model) ? modelData[root.textRole] : model[root.textRole])
                  : modelData
            color: settingsManager.theme.popupFontColor
            font.family: root.font.family
            font.pointSize: root.font.pointSize
            font.bold: root.currentIndex == index
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
        }
        background: Rectangle {
            color: parent.highlighted ? settingsManager.theme.highlightColor : "transparent"
        }
        highlighted: root.highlightedIndex === index
    }

    indicator: Canvas {
        id: canvas
        x: root.width - width - root.rightPadding
        y: root.topPadding + (root.availableHeight - height) / 2
        width: 12
        height: 8
        contextType: "2d"

        onPaint: {
            context.reset()
            context.moveTo(0, 0)
            context.lineTo(width, 0)
            context.lineTo(width / 2, height)
            context.closePath()
            context.fillStyle = settingsManager.theme.popupIconColor
            context.fill()
        }

        Connections {
            target: settingsManager
            onThemeChanged: {
                canvas.requestPaint()
            }
        }
    }

    contentItem: Text {
        leftPadding: 5
        rightPadding: root.indicator.width + root.spacing

        text: root.displayText
        font: root.font
        color: settingsManager.theme.popupFontColor
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        implicitWidth: 120
        implicitHeight: 40
        color: settingsManager.theme.controlColor
        radius: 2
    }

    popup: Popup {
        y: root.height
        width: root.width
        implicitHeight: contentItem.implicitHeight
        padding: 0

        contentItem: ListView {
            clip: true
            implicitHeight: contentHeight
            model: root.popup.visible ? root.delegateModel : null
            currentIndex: root.highlightedIndex

            ScrollIndicator.vertical: ScrollIndicator { }
        }

        background: Rectangle {
            color: settingsManager.theme.controlColor
            radius: 2
        }
    }
}
