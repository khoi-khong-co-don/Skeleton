import QtQuick 2.0
import QtQuick.Controls 2.0
import HMIEVENTS 1.0
import "./../../../QAppFramework/QQml/Common" as Common

Common.QRootScreen {

    MouseArea {
        width:  parent.width
        height: parent.height

        preventStealing: true
    }
    MouseArea {
        width: parent.width - rec1.width
        height: parent.height
        anchors.top: parent.top
        anchors.right: parent.right
        onClicked: {
            console.log("aaaaaaa")
            QMLHandle.sendEvent(EVT.EVT_POPUP_B_BUTTON_XXX_CLICKED)
        }
        preventStealing: true
    }


    Rectangle {
        id: rec1
        width: 350
        height: 60
        color: "#2D3840"
        border.color: "#2D3840"

        Text {
            anchors.left: parent.left
            anchors.leftMargin: 70  // Khoảng cách từ viền trái của hình chữ nhật
            anchors.verticalCenter: parent.verticalCenter  // Căn giữa dọc văn bản
            text: qsTr("Log in to Oryza Cloud")
            font.pixelSize: 18
            color: "white"
        }

        Image {
            id: one
            source: "qrc:/cloud_icon.png"
            height: 35
            width: 35
            x: 15       // Khoảng cách từ lề trái
            anchors.verticalCenter: parent.verticalCenter  // Căn giữa theo chiều dọc
            fillMode: Image.PreserveAspectFit  // Đảm bảo hình ảnh không bị méo khi thay đổi kích thước
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                QMLHandle.sendEvent(EVT.EVT_SCREEN_B_BUTTON_ZZZ_CLICKED)
            }
        }
    }


    Row {
        anchors.bottom: parent.bottom

        Rectangle {
            width: 350
            height: 732
            color: "#263237"
            border.color: "#232F34"

            Text {
                width: 200
                height: 150
                x: 50
                text: qsTr("New connection")
                font.pixelSize: 18
                color: "white"
                anchors.bottom: parent.bottom

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        QMLHandle.sendEvent(EVT.EVT_SCREEN_B_BUTTON_YYY_CLICKED)
                    }
                }
            }

            Image {
                id: two
                source: "qrc:/cloud_icon.png"
                height: 35
                width: 35
                x: 10       // Khoảng cách từ lề trái
                y: 600
                fillMode: Image.PreserveAspectFit  // Đảm bảo hình ảnh không bị méo khi thay đổi kích thước
            }

            Text {
                width: 200
                height: 100
                x: 50
                text: qsTr("Settings")
                font.pixelSize: 18
                color: "white"
                anchors.bottom: parent.bottom

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        QMLHandle.sendEvent(EVT.EVT_SCREEN_B_BUTTON_YYY_CLICKED)
                    }
                }
            }

            Image {
                id: three
                source: "qrc:/cloud_icon.png"
                height: 35
                width: 35
                x: 10       // Khoảng cách từ lề trái
                y: 645      // Khoang cach tu tren xuong
                fillMode: Image.PreserveAspectFit  // Đảm bảo hình ảnh không bị méo khi thay đổi kích thước
            }

            Text {
                width: 200
                height: 50
                x: 15
                text: qsTr("Version:......")
                font.pixelSize: 16
                color: "white"
                anchors.bottom: parent.bottom

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        QMLHandle.sendEvent(EVT.EVT_SCREEN_B_BUTTON_YYY_CLICKED)
                    }
                }
            }
        }
    }
}








