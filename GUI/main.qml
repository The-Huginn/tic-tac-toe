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
    color: "#ff0000"

    Grid {
        columns: 1
        rows: 2
        width: parent.width
        height: parent.height

        Rectangle {
            id: menu
            width: appWindow.width
            height: 80
            color: "black"

            GridLayout {
                anchors.fill: parent
                RoundButton {
                    Layout.alignment: Qt.AlignCenter
                    implicitWidth: 100
                    text: "New Game"
                    radius: 20
                }
                RoundButton {
                    Layout.alignment: Qt.AlignCenter
                    text: "Settings"
                    radius: 20
                    implicitWidth: 100
                }
            }
        }

        Rectangle {
            width: appWindow.width
            height: appWindow.height - menu.height
            color: "transparent"

            ScrollView {
//                anchors.centerIn: parent;
                width: parent.width
                height: parent.height
                // +50 for wiggle room
                contentWidth: Math.max(layout.width + 50, parent.width)
                contentHeight: Math.max(layout.height + 50, parent.height)

                clip: true

                Flickable {
                    anchors.centerIn: parent

                    Grid {
                        id: layout
                        anchors.centerIn: parent
                        rows: Game.getHeight()
                        columns: Game.getWidth()
                        spacing: 10

                        // Create layout for the game
                        Repeater {
                            id: gameRepeater
                            model: Game.getHeight() * Game.getWidth()
                            GameWindow {
                                row: index / Game.getWidth()
                                column: index % Game.getWidth()
                            }
                        }
                    }

                    // Create vertical lines
                    Grid {
                        anchors.centerIn: parent
                        rows: 1
                        columns: Game.getWidth() - 1
                        spacing: 100    // 100 is height of GameWindow
                        Repeater {
                            model: Game.getWidth() - 1
                            Rectangle {
                                color: "#000000"
                                radius: 10
                                width: layout.spacing
                                height: 100 * Game.getHeight() + (layout.spacing * Game.getHeight() - 1)    // 100 is height of GameWindow
                            }
                        }
                    }

                    // Create horizontal lines
                    Grid {
                        anchors.centerIn: parent
                        rows: Game.getHeight() - 1
                        columns: 1
                        spacing: 100    // 100 is width of GameWindow
                        Repeater {
                            model: Game.getHeight() - 1
                            Rectangle {
                                color: "#000000"
                                radius: 10
                                width: 100 * Game.getWidth() + (layout.spacing * Game.getWidth() - 1)   // 100 is width of GameWindow
                                height: layout.spacing
                            }
                        }
                    }
                }
            }
        }
    }
}
