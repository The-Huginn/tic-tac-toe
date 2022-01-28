import QtQuick 2.3
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
import Game 1.0

Rectangle {
    width: 100
    height: 100
    property int row: 0
    property int column: 0
    color: "transparent"
    Image {
        anchors.centerIn: parent
        width: 90
        height: 90
        signal clicked()
        property int row: parent.row
        property int column: parent.column
        MouseArea {
            anchors.fill: parent
            onClicked: {
                Game.playRound(row, column)
                if (Game.getSquare(row, column) === 1)
                    parent.source = "images/cross.svg"
                if (Game.getSquare(row, column) === 2)
                    parent.source = "images/nought.svg"
            }
        }
    }
}
