import QtQuick 2.15
import QtQuick.Controls 2.15
import HMIEVENTS 1.0
import "./../../../QAppFramework/QQml/Common" as Common
Common.QRootScreen {
    Rectangle {anchors.fill: parent; color: "black"}

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
        color : "#212A2F"
        Row {
            anchors.top: parent.top
            anchors.left: parent.left
            width: parent.width
            spacing: 40
            Image {
                id: backicon

                anchors.top: parent.top
                anchors.topMargin: 8
                anchors.left: parent.left
                anchors.leftMargin: 15

                width: 25
                height: 25
                source: "qrc:/back.png"

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        QMLHandle.sendEvent(EVT.EVT_POPUP_edit_server_BUTTON_BACK_CLICKED)
                    }
                }
            }
            Text {
                id: usernameText
                anchors.left: backicon.right
                anchors.leftMargin: 10
                anchors.top: parent.top
                anchors.topMargin: 8
                text: mainModelServer.name
                color: "White"
                font.pixelSize: 20
            }
        }
    }


    Rectangle{
        id: info
        width: parent.width
        height: parent.height - topbar.height
        anchors.top: topbar.bottom
        anchors.left: parent.left
        anchors.topMargin: 2
        color : "#212A2F"


        Column {
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 20
            width: parent.width - 50
            height: parent.height
            spacing: 20

            TextField {
                id: ipField
                //placeholderText: "localhost:port"
                text: ediServerModel.server
                //echoMode: TextInput.Password
                color: "white"
                width: parent.width
                height: 50
                background: Rectangle {
                    width: parent.width
                    color: "transparent"  // Màu xanh nhạt
                    border.color: ipField.activeFocus ? "#5A9BD5" : "#303F47"
                    border.width: 1
                    radius: 5
                }
                onActiveFocusChanged: {
                    if (activeFocus) {
                        ipField.activeFocus = false;  // Bỏ tương tác khỏi passwordField
                    }
                }

            }


            TextField {

                id: usernameField
                //placeholderText: "Username"
                text: ediServerModel.username
                //echoMode: TextInput.data
                width: parent.width
                color: "white"
                height: 50
                background: Rectangle {
                    color: "transparent"
                    border.color: usernameField.activeFocus ? "#5A9BD5" : "#303F47"
                    border.width: 1
                    radius: 5
                }
                onActiveFocusChanged: {
                    if (activeFocus) {
                        usernameField.activeFocus = false;  // Bỏ tương tác khỏi passwordField
                    }
                }
            }

            TextField {
                id: passwordField
                //placeholderText: "Password"
                text: ediServerModel.password
                echoMode: TextInput.Password
                color: "white"
                width: parent.width
                height: 50
                background: Rectangle {
                    width: parent.width
                    color: "transparent"  // Màu xanh nhạt
                    border.color: passwordField.activeFocus ? "#5A9BD5" : "#303F47"
                    border.width: 1
                    radius: 5
                }
                onActiveFocusChanged: {
                    if (activeFocus) {
                        passwordField.activeFocus = false;  // Bỏ tương tác khỏi passwordField
                    }
                }

            }

            Button {
                palette {
                    button: "#2FA2DB"
                }
                width: parent.width
                text: "Connect"
                palette.buttonText: "white"
                onClicked: {

                }
            }
            Button {
                palette {
                    button: "#2B383F"
                }
                width: parent.width
                text: "Delete"
                palette.buttonText: "white"
                onClicked: {
                    //notification.show()
                }
            }
        }

    }


}
