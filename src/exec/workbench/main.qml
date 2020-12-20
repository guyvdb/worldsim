import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import MapCanvas 1.0


Window {

    visible: true
    title: qsTr("World Workbench")

    Rectangle {
        id: viewport
        anchors.fill: parent
        color: "black"

        Rectangle {
            id: toolbar
            color: "yellow"
            anchors.left: parent.left;
            anchors.top:  parent.top;
            anchors.right: parent.right;
            height: 44
            anchors.margins: 4


            Row {
                anchors.margins: 8
                Button {
                    id: btnQuit
                    text: "Quit"

                    onClicked: {
                        Qt.quit()
                    }
                }

                Button {
                    id: btnRender
                    text: "Render"

                    onClicked: {
                        bridge.render()
                        mapCanvas.redraw()
                    }
                }
            }
        }

        MapCanvas {
            id: mapCanvas

           anchors.left: parent.left
           anchors.right: parent.right
           anchors.top: toolbar.bottom
           anchors.bottom: parent.bottom

        }

    }





}
