import QtQuick 2.3
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.2
import Game 1.0

Rectangle {
    id: gameWindow
    height: appWindow.height
    width: appWindow.width
    color: "transparent"

    ColumnLayout {
        width: children.width
        height: children.height

        Rectangle {
            id: menu
            width: gameWindow.width
            height: 80
            color: "#88000000"


            ColumnLayout {
                width: menu.width
                height: menu.height - 10

                RowLayout {
                    width: menu.width
                    height: menu.height
                    Rectangle {
                        id: crossWinnerRect
                        Layout.preferredWidth: 1
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        color: "transparent"

                        Text {
                            anchors.centerIn: parent
                            font.italic: true
                            text: qsTr("Cross wins: " + Game.getCrossWins())
                            color: "yellow"
                        }
                    }

                    Rectangle {
                        id: noughtWinnerRect
                        Layout.preferredWidth: 1
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        color: "transparent"

                        Text {
                            anchors.centerIn: parent
                            font.italic: true
                            text: qsTr("Nought wins: " + Game.getNoughtWins())
                            color: "yellow"
                        }
                    }

                    Rectangle {
                        id: drawRect
                        Layout.preferredWidth: 1
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        color: "transparent"

                        Text {
                            anchors.centerIn: parent
                            font.italic: true
                            text: qsTr("Draws: " + Game.getDraws())
                            color: "yellow"
                        }
                    }
                }

                RowLayout {
                    width: menu.width
                    height: menu.height
                    Layout.alignment: Qt.AlignCenter

                    Rectangle {
                        id: newGameRect
                        Layout.preferredWidth: 1
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        color: "transparent"

                        RoundButton {
                            anchors.centerIn: parent
                            width: parent.width / 2
                            text: "New Game"
                            radius: 20

                            onClicked: {
                                Game.newGame()
                                loader.active = false
                                loader.source = "GameWindow.qml"
                                loader.active = true
                            }
                        }
                    }

                    Rectangle {
                        id: settingsRect
                        Layout.preferredWidth: 1
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        color: "transparent"

                        RoundButton {
                            anchors.centerIn: parent
                            width: parent.width / 2
                            text: "Settings"
                            radius: 20

                            onClicked: loader.source = "Settings.qml"
                        }
                    }
                }
            }
        }

        Rectangle {
            width: appWindow.width
            height: appWindow.height - menu.height
            color: "transparent"

            ScrollView {

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
                            Square {
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
                        spacing: 100    // 100 is height of Square
                        Repeater {
                            model: Game.getWidth() - 1
                            Rectangle {
                                color: "#000000"
                                radius: 10
                                width: layout.spacing
                                height: 100 * Game.getHeight() + (layout.spacing * Game.getHeight() - 1)    // 100 is height of Square
                            }
                        }
                    }

                    // Create horizontal lines
                    Grid {
                        anchors.centerIn: parent
                        rows: Game.getHeight() - 1
                        columns: 1
                        spacing: 100    // 100 is width of Square
                        Repeater {
                            model: Game.getHeight() - 1
                            Rectangle {
                                color: "#000000"
                                radius: 10
                                width: 100 * Game.getWidth() + (layout.spacing * Game.getWidth() - 1)   // 100 is width of Square
                                height: layout.spacing
                            }
                        }
                    }
                }
            }
        }
    }
}
