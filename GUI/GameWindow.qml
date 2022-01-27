import QtQuick 2.3
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
import Game 1.0

Image {
    width: 100
    height: 100
    signal clicked()
    property int row: 0
    property int column: 0
    source: {
        source = "images/none.svg"
        if (Game.getSquare(row, column) === 1)
            source = "images/cross.svg"
        if (Game.getSquare(row, column) === 2)
            source = "images/nought.svg"
    }

    Component.onCompleted: {
        console.log("row: ", row, "column", column)
    }
}
