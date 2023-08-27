/* Khoi */

import QtQuick 2.0
import HMIEVENTS 1.0
import "./../../../QAppFramework/QQml/Common" as Common

import QtQuick.Window 2.0
import QtQml.Models 2.1
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtLocation 5.3
import QtPositioning 5.2

Common.QRootScreen {
    id:test
    Rectangle {anchors.fill: parent; color: "black"}
    onIsOnTopChanged: {
        console.log(" ThanhNV: ", isOnTop)
        console.log(" ThanhNV: ", viewerIndex)
        console.log(" ThanhNV: ", viewerIndexWidth)
        console.log(" ThanhNV: ", viewerIndexHeight)
       // console.log(qsTr("Value of ThanhNV22:") + " " + ThanhNV22.toString());
    }

    Row {

        anchors.horizontalCenter: parent.horizontalCenter  // Center the row horizontally
        id : bottombar
        anchors.bottom: parent.bottom

        spacing: 40

        Rectangle {
            width: 400
            height: 40
            color: "#355E3B"  // Set the background color to gray
            border.color: "#294C2F"
            radius: 5  // Add rounded corners to the rectangle

            anchors.horizontalCenter: parent.horizontalCenter

            anchors.bottom: parent.bottom

            Text {
                text: qsTr("Connect to Another Server...")
                //text: ThanhNV22
                color: "white"
                anchors.centerIn: parent  // Center the text both vertically and horizontally
                horizontalAlignment: Text.AlignHCenter  // Center the text horizontally
                verticalAlignment: Text.AlignVCenter  // Center the text vertically
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    QMLHandle.sendEvent(EVT.EVT_SCREEN_B_BUTTON_XXX_CLICKED)
                }
            }
        }
    }


    Row {
        id: topbar
        anchors.top: parent.top
        //anchors.topMargin: 10
        spacing: 40

        Image {
            id: one
            width: 70
            height: 40
            source: "qrc:/main_menu.png"
            MouseArea {
                anchors.fill: one
                onClicked: {
                    QMLHandle.sendEvent(EVT.EVT_SCREEN_B_BUTTON_YYY_CLICKED)
                    console.log("bbbbbbbbbbbbb");
                }
            }
        }


        Text {
            anchors.left: topbar.left
            anchors.leftMargin: 250
            //text: "Login Nx Cloud"
            text: editServer.get(0).name
            color: "White"
            font.pixelSize: 20
            //anchors.right: parent.left
        }

    }


    ListView {
        id: listView

        width: parent.width
        height: parent.height
        anchors.top: topbar.bottom
        anchors.topMargin: 50
        anchors.bottom: bottombar.top
        anchors.bottomMargin: 50
        orientation: ListView.Vertical
        spacing :2
        model: mainModelServer
        ScrollBar.horizontal: ScrollBar {
            orientation: Qt.Vertical
            //size: listViewId.width / listViewId.contentWidth
            anchors.top: listView.top
            anchors.topMargin: 10
            anchors.left: listView.left
            visible: listView.count > 6
        }

        clip : true
        delegate: Item {
            id: dlg

            property int dlg_i: index
            width: parent.width
            height: 100
            Rectangle {
                id : item_rec
                width: parent.width
                height: 95
                color: "#1C2328"
                visible: true

                Column {
                    id: text_server
                    spacing: 5
                    anchors.fill: parent
                    anchors.leftMargin: 20
                    anchors.topMargin: 10
                    Text {
                        text: model.name
                        color:  model.connect === "true" ? "white" : "#3F545F"
                        font.pixelSize: 20
                    }

                    RowLayout {
                        spacing: 2

                        Image {
                            source: model.connect === "true" ? "qrc:/server.png" : "qrc:/server_offline.png"
                            width: 20
                            height: 20
                        }

                        Text {
                            text: model.server
                            color: model.connect === "true" ? "white" : "#3F545F"
                            font.pixelSize: 20
                        }
                    }

                    RowLayout {
                        spacing: 2

                        Image {
                            source: model.connect === "true" ? "qrc:/user.png" : "qrc:/user_offline.png"
                            width: 10
                            height: 10
                        }

                        Text {
                            text: username
                            color: model.connect === "true" ? "white" : "#3F545F"
                            font.pixelSize: 20
                        }
                    }
                }
                Rectangle {
                    id: text_off
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 10
                    anchors.right: parent.right
                    anchors.rightMargin: 20
                    width: 90
                    height: 25
                    radius: 5
                    color: "#445B67"
                    Text {
                        anchors.centerIn: parent
                        text: qsTr("OFFLINE")
                        font.pixelSize: 15
                        color: "white"
                    }
                    visible: model.connect === "false"
                }


                MouseArea {
                    id: mouseArea_server
                    anchors.fill: parent
                    onClicked: {

                        QMLHandle.registerContextProperty("index", dlg.dlg_i);

                        QMLHandle.sendEvent(EVT.EVT_SCREEN_B_BUTTON_SERVER_CLICKED)

                    }
                    Rectangle {
                        id : edit_rec
                        anchors.top: parent.top
                        anchors.topMargin: 10
                        anchors.right: parent.right
                        anchors.rightMargin: 60
                        Image {
                            id: edit_img
                            source: "qrc:/edit_hovered@2x.png"
                            width: 40
                            height: 40

                            MouseArea {
                                id: mouseArea_edit
                                anchors.fill: parent
                                onClicked: {

                                    QMLHandle.sendEvent(EVT.EVT_SCREEN_B_BUTTON_EDIT_SERVER_CLICKED, model.address)
                                    console.log("   popup edit ")
                                    mainModelServer.sendMsg("Hello World!!!")
                                }

                                propagateComposedEvents: true
                            }
                        }

                        visible: model.login === "true"
                    }
                }
            }
        }
    }
}



