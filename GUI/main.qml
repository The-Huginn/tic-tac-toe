import QtQuick 2.3
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.2
import Game 1.0

ApplicationWindow {
    id: appWindow
    width: 640
    height: 480
    minimumWidth: 400
    minimumHeight: 450
    visible: true
    title: qsTr("Tic Tac Toe")
//    color: "#ff0000"

    Loader {
            id: loader
            onSourceChanged: animation.start()

            NumberAnimation {
                id: animation
                target: loader.item
                property: "y"
                from: appWindow.height
                to: 0
                duration: 1000
                easing.type: Easing.OutCubic
            }
        }

    Component.onCompleted: loader.source = "GameWindow.qml"
}
