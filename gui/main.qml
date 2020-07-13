import QtQuick 2.2
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

ApplicationWindow {
    id: appWindow
    title: "Racking System Optimizer"
    visible: true
    visibility: "Maximized"
    minimumWidth: 640
    minimumHeight: 480

    property int margin: 11

    property alias forkliftModel: forklift.model
    property alias inputBufferModel: inputBuffer.model
    property variant blockModel

    component PalletDelegate : Rectangle {
        required property int index
        required property string product
        required property double size
        required property double quantity
        height: 30
        width: 150
        color: "#ABC"
        opacity: product == "" ? 0.5 : 1
        border.width: 1
        Text {
            visible: product != ""
            text: "Product " + product + ", qty: "+quantity+" ("+size+" m)"
            anchors.centerIn: parent
        }
    }

    RowLayout {
        id: mainLayout
        anchors.fill: parent
        anchors.margins: appWindow.margin
        spacing: appWindow.margin

        ColumnLayout {
            id: leftPaneLayout
            spacing: appWindow.margin
            Layout.fillHeight: true
            Layout.minimumWidth: 174
            Layout.maximumWidth: 174

            GroupBox {
                title: "Forklift"
                Layout.fillWidth: true
                Layout.minimumHeight: 82
                Layout.maximumHeight: 82

                ListView {
                    id: forklift
                    anchors.fill: parent
                    required model
                    delegate: PalletDelegate {}
                }
            }

            GroupBox {
                title: "Input Buffer"
                Layout.fillWidth: true
                Layout.fillHeight: true

                ScrollView {
                    anchors.fill: parent
                    anchors.margins: 0
                    clip: true
                    ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
                    ScrollBar.vertical.policy: ScrollBar.AsNeeded
                    ScrollBar.vertical.interactive: true

                    ListView {
                        id: inputBuffer
                        anchors.fill: parent
                        spacing: appWindow.margin
                        required model
                        delegate: PalletDelegate {
                            MouseArea {
                                anchors.fill: parent
                                onClicked: inputBufferModel.interact(index)
                            }
                        }
                    }
                }
            }
        }

        ColumnLayout {
            id: rightPaneLayout
            spacing: appWindow.margin
            Layout.fillWidth: true

            RowLayout {
                spacing: appWindow.margin
                GroupBox {
                    title: "Front View"
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    ButtonGroup { id: laneGroup }

                    ListView {
                        id: frontView
                        anchors.fill: parent
                        orientation: ListView.Horizontal
                        model: blockModel
                        spacing: appWindow.margin

                        delegate: ColumnLayout {
                            width: 152
                            height: parent.height

                            ListView {
                                id: laneView
                                Layout.fillHeight: true
                                width: parent.width
                                model: submodel
                                spacing: appWindow.margin
                                verticalLayoutDirection: ListView.BottomToTop
                                delegate: PalletDelegate {
                                    MouseArea {
                                        anchors.fill: parent
                                        onClicked: laneView.model.interact(index)
                                    }
                                }
                            }

                            RadioDelegate {
                                Layout.alignment: Qt.AlignHCenter
                                ButtonGroup.group: laneGroup
                                checked: index == 0
                                text: "Lane " + index
                                onCheckedChanged: function() {
                                    if (checked) sideView.model = submodel
                                }
                            }
                        }
                    }
                }

                GroupBox {
                    title: "Side View"
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    ListView {
                        id: sideView
                        anchors.fill: parent
                        width: parent.width
                        verticalLayoutDirection: ListView.BottomToTop
                        spacing: appWindow.margin

                        delegate: ListView {
                            id: rowView
                            width: parent.width
                            height: 32
                            model: submodel
                            spacing: appWindow.margin
                            orientation: ListView.Horizontal
                            layoutDirection: ListView.RightToLeft
                            delegate: PalletDelegate {
                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: rowView.model.interact(index)
                                }
                            }
                        }

                        Rectangle {
                            id: wall
                            anchors.left: parent.left
                            width: 2
                            height: parent.height
                            border.width: 2
                            color: "transparent"
                        }
                    }
                }
            }

            GroupBox {
                id: bottomPane
                title: "Controls and Information"
                Layout.fillWidth: true
                Layout.minimumHeight: 200
                Layout.maximumHeight: 400
            }
        }
    }
}
