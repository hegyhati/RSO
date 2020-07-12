import QtQuick 2.2
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

ApplicationWindow {
    id: appWindow
    title: "Racking System Optimizer"
    visible: true
    visibility: "Maximized"
    property int margin: 11

    property alias forkliftModel: forklift.model
    property alias inputBufferModel: inputBuffer.model

    component PalletDelegate : Rectangle {
        required property int index
        required property string product
        required property double size
        required property double quantity
        height: 30
        width: parent.width
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
            Layout.minimumWidth: 150
            Layout.maximumWidth: 250

            GroupBox {
                title: "Forklift"
                Layout.fillWidth: true
                Layout.minimumHeight: 72

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
                    id: frontView
                    title: "Front View"
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }

                GroupBox {
                    id: sideView
                    title: "Side View"
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }
            }

            GroupBox {
                id: bottomPane
                title: "Controls and Information"
                Layout.fillWidth: true
            }
        }
    }
}
