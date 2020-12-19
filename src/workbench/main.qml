import QtQuick 2.15
import QtQuick.Window 2.15



Window {
    width: maximumWidth
    height: maximumHeight
    visible: true
    title: qsTr("World Workbench")

    MouseArea {
        anchors.fill: parent
        onClicked: {
            world.hello()
            Qt.quit()
        }
    }

    Rectangle {
        id: viewport
        anchors.fill: parent
        color: "black"
    }

    Rectangle {
        id: menu
        anchors.left: viewport.left
        anchors.right: viewport.right
        anchors.top: viewport.top
        height: 20
        color: "white"
    }

    MainMenu {
        id: mainMenu
        anchors.centerIn: viewport

    }

    Canvas {
        anchors.left: viewport.left
        anchors.right: viewport.right
        anchors.bottom: viewport.bottom
        anchors.top: viewport.top + 20

        onPaint: {
            var ctx = getContext("2d")
            ctx.line
        }

        visible: false

    }

}
