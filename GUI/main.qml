import QtQuick 2.3
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
import Game 1.0

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Tic Tac Toe")

    Grid {
        x: 5
        y: 5
        rows: Game.getHeight()
        columns: Game.getWidth()
        spacing: 10
        Repeater { model: Game.getHeight() * Game.getWidth()
            GameWindow {
                row: index / Game.getWidth()
                column: index % Game.getWidth()
            }
        }
    }
}
