import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.5
import Game 1.0

Rectangle {
    id: square
    width: 100
    height: 100
    property int row: 0
    property int column: 0
    color: "transparent"

    Image {
        id: image
        anchors.centerIn: parent
        width: 90
        height: 90
        source: {
            if (Game.getSquare(row, column) === 1)
                return "images/cross.svg"
            if (Game.getSquare(row, column) === 2)
                return "images/nought.svg"
            return ""
        }

        property int row: parent.row
        property int column: parent.column
        MouseArea {
            anchors.fill: parent
            onClicked: {
                var winner = Game.playRound(row, column)
                if (Game.getSquare(row, column) === 1)
                    parent.source = "images/cross.svg"
                if (Game.getSquare(row, column) === 2)
                    parent.source = "images/nought.svg"
                if (winner !== 0) {
                    loader.source = "Result.qml"
                }
                imageAnimation.start()
            }
        }

        NumberAnimation {
            id: imageAnimation
            target: image
            property: "opacity"
            from: 0
            to: 1
        }
    }
}
