import QtQuick 2.0
import QtQuick.Controls 2.0
import HMIEVENTS 1.0
import "./../../../QAppFramework/QQml/Common" as Common

Common.QRootScreen {
    Rectangle {anchors.fill: parent; color: "Black"}
    MouseArea {
        width:  parent.width
        height: parent.height
        preventStealing: true
    }


    Rectangle{
        id: topbar
        width: parent.width
        height: 40

        anchors.top: parent.top
        anchors.left: parent.left
        //anchors.topMargin: 10
        color : "#212A2F"           //#212A2F
        Row {
            anchors.top: parent.top
            anchors.left: parent.left
            width: parent.width
            spacing: 40
            Image {
                id: backIcon

                anchors.top: parent.top
               // anchors.topMargin: 8
                anchors.left: parent.left
              //  anchors.leftMargin: 15

                width: 70
                height: 40
                source: "qrc:/main_menu.png"

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        //QMLHandle.sendEvent(EVT.EVT_POPUP_edit_server_BUTTON_BACK_CLICKED)
                    }
                }
            }
            //search_selected.png
            Text {
                id: usernameText
                anchors.left: backIcon.right
                anchors.leftMargin: 10
                anchors.top: parent.top
                anchors.topMargin: 8
                text: Name
                color: "White"
                font.pixelSize: 20
            }
            Image {
                id: searchIcon

                anchors.top: parent.top
               // anchors.topMargin: 8
                anchors.right: parent.right
              //  anchors.leftMargin: 15

                width: 40
                height: 40
                source: "qrc:/search_selected.png"

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        //QMLHandle.sendEvent(EVT.EVT_POPUP_edit_server_BUTTON_BACK_CLICKED)
                    }
                }
            }
        }
    }

}



