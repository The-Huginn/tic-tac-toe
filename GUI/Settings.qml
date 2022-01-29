import QtQuick 2.3
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.15
import Game 1.0

Rectangle {
    id: settings
    width: appWindow.width
    height: appWindow.height
    color: "transparent"

    property int maxSlider: 20

    MouseArea {
        anchors.fill: parent
        onClicked: forceActiveFocus()
    }

    ColumnLayout {
        Layout.fillHeight: false
        anchors.fill: parent
        anchors.margins: 40
        spacing: 20

        GridLayout {
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter

            width: parent.width

            rows: 3
            columns: 3
            columnSpacing: 10

            Text {
                id: heightText
                Layout.alignment: Qt.AlignHCenter
                text: "Height"
            }

            Text {
                id: widthText
                Layout.alignment: Qt.AlignHCenter
                text: "Width"
            }

            Text {
                id: minimumText
                Layout.alignment: Qt.AlignHCenter
                text: "Minimum Connected"
            }

            Slider {
                id: heightSlider
                Layout.fillWidth: true
                property alias currentValue: heightSlider.value
                from: Game.minimumHeight()
                value: Game.nextHeight()
                to: maxSlider
                stepSize: 1
                snapMode: Slider.SnapAlways

                onMoved: {
                    var before = Game.nextMinimum()
                    Game.changeHeight(parseInt(value))
                    heightField.name = Game.nextHeight()    // to ensure we display current setting

                    // Check for minimum to update
                    var after = Game.nextMinimum()
                    if (before !== after)
                    {
                        minimumSlider.currentValue = after
                        minimumField.name = after
                    }
                }
            }

            Slider {
                id: widthSlider
                Layout.fillWidth: true
                property alias currentValue: widthSlider.value
                from: Game.minimumWidth()
                value: Game.nextWidth()
                to: maxSlider
                stepSize: 1
                snapMode: Slider.SnapAlways

                onMoved: {
                    var before = Game.nextMinimum()
                    Game.changeWidth(parseInt(value))
                    widthField.name = Game.nextWidth()    // to ensure we display current setting

                    // Check for minimum to update
                    var after = Game.nextMinimum()
                    if (before !== after)
                    {
                        minimumSlider.currentValue = after
                        minimumField.name = after
                    }
                }
            }

            Slider {
                id: minimumSlider
                Layout.fillWidth: true
                property alias currentValue: minimumSlider.value
                from: Game.minimumSquares()
                value: Game.nextMinimum()
                to: maxSlider
                stepSize: 1
                snapMode: Slider.SnapAlways

                onMoved: {
                    Game.changeMinimum(parseInt(value))
                    minimumField.name = Game.nextMinimum()    // to ensure we display current setting
                    value = Game.nextMinimum()
                }
            }

            TextField {
                id: heightField
                Layout.fillWidth: true
                property alias name: heightField.text
                placeholderText: Game.nextHeight()
                validator: IntValidator {
                    bottom: Game.minimumHeight()
                    top: 1000
                    }

                onFocusChanged: {
                    if (!activeFocus)
                    {
                        var before = Game.nextMinimum()
                        Game.changeHeight(parseInt(text))
                        text = Game.nextHeight()    // to ensure we display current setting

                        // Check for minimum to update
                        var after = Game.nextMinimum()
                        if (before !== after)
                        {
                            minimumSlider.currentValue = after
                            minimumField.name = after
                        }

                        // Update Slider
                        heightSlider.currentValue = Math.min(Game.nextHeight(), maxSlider)
                    }
                }
            }

            TextField {
                id: widthField
                Layout.fillWidth: true
                property alias name: widthField.text
                placeholderText: Game.nextWidth()
                validator: IntValidator {
                    bottom: Game.minimumWidth()
                    top: 1000
                    }

                onFocusChanged: {
                    if (!activeFocus)
                    {
                        var before = Game.nextMinimum()
                        Game.changeWidth(parseInt(text))
                        text = Game.nextWidth()    // to ensure we display current setting

                        // Check for minimum to update
                        var after = Game.nextMinimum()
                        if (before !== after)
                        {
                            minimumSlider.currentValue = after
                            minimumField.name = after
                        }

                        // Update Slider
                        widthSlider.currentValue = Math.min(Game.nextWidth(), maxSlider)
                    }
                }
            }

            TextField {
                id: minimumField
                Layout.fillWidth: true
                property alias name: minimumField.text
                placeholderText: Game.nextMinimum()
                validator: IntValidator {
                    bottom: Game.minimumSquares()
                    top: 1000
                    }

                onFocusChanged: {
                    if (!activeFocus)
                    {
                        Game.changeMinimum(parseInt(text))
                        text = Game.nextMinimum()    // to ensure we display current setting

                        // Update Slider
                        minimumSlider.currentValue = Math.min(Game.nextMinimum(), maxSlider)
                    }
                }
            }
        }

        Text {
            Layout.alignment: Qt.AlignHCenter
            font.italic: true
            font.pointSize: 8
            text: qsTr("Note: Settings are automatically saved for the next game")
        }

        RowLayout {
            Layout.alignment: Qt.AlignBottom | Qt.AlignHCenter

            Rectangle {
                Layout.preferredWidth: 1
                Layout.fillWidth: true
                Layout.fillHeight: true
                color: "transparent"

                RoundButton {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.bottom
                    width: parent.width / 2
                    implicitWidth: 100
                    text: "Continue"
                    radius: 20

                    onClicked: {
                        loader.source = "GameWindow.qml"
                    }
                }
            }

            Rectangle {
                Layout.preferredWidth: 1
                Layout.fillWidth: true
                Layout.fillHeight: true
                color: "transparent"

                RoundButton {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.bottom
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
        }
    }
}
