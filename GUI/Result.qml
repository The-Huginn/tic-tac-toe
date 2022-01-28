import QtQuick 2.3
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
import Game 1.0

Rectangle {
    id: result
    height: appWindow.height
    width: appWindow.width
    color: "#000000"

    MouseArea {
        anchors.fill: parent
        Text {
            id: textAppearence
            anchors.centerIn: parent
            text: {
                if (Game.nextPlayer() === 1)
                    return "Cross is winner!"
                if (Game.nextPlayer() === 2)
                    return "Nought is winner!"
                return "It's a draw!"
            }
            font.italic: true
            font.pointSize: 24
            color: "green"
            NumberAnimation {
                id: textAppearenceAnim
                target: textAppearence
                property: "opacity"
                from: 0
                to: 1
                duration: 2000
            }
        }

        onClicked: {
            Game.newGame()
            loader.source = "GameWindow.qml"
        }
    }
    Component.onCompleted: textAppearenceAnim.start()
}
