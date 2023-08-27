import QtQuick 2.0
import QtQuick.Controls 2.0
import HMIEVENTS 1.0
import "./../../../QAppFramework/QQml/Common" as Common

Common.QRootScreen {
    Rectangle {anchors.fill: parent; color: "darkslategray"}

    Image {
        id: one
        source: "qrc:/cloud_icon.png"
        height: 35
        width: 35
        x: 30  // Khoảng cách từ lề trai
        y: 30      // Khoang cach tu tren xuong duoi
        fillMode: Image.PreserveAspectFit  // Đảm bảo hình ảnh không bị méo khi thay đổi kích thước

        MouseArea {
            anchors.fill: parent
            onClicked: {
                QMLHandle.sendEvent(EVT.EVT_SCREEN_NX_LOGIN_CLOUD_BUTTON_BACK_CLICKED)
            }
        }
    }

    Image {
        id: two
        source: "qrc:/cloud_icon.png"
        height: 90
        width: 90
        anchors.horizontalCenter: parent.horizontalCenter
        y: 120
        fillMode: Image.PreserveAspectFit  // Đảm bảo hình ảnh không bị méo khi thay đổi kích thước
        }


    Rectangle {
        width: 350
        height: 40
        border.color: "blue"  // Màu của viền đen
        color: "blue"  // Màu nền đen
        border.width: 2
        y: 450
        anchors.horizontalCenter: parent.horizontalCenter  // Căn giữa theo chiều ngang

        TextField {
                width: parent.width
                height: parent.height
                placeholderText: qsTr("Enter your email")  // Placeholder text when the field is empty
                color: "black"
                selectionColor: "lightblue"  // Color of the selected text
                cursorVisible: true  // Show the text cursor
                selectByMouse: true   // Allow text selection using the mouse
                horizontalAlignment: Text.AlignLeft  // Center the text horizontally
                verticalAlignment: Text.AlignVCenter  // Center the text vertically
                background: Rectangle {
                                color: "dimgrey" // Màu nền của TextField
                                border.color: "black"  // Màu khung của TextField
                                border.width: 1        // Độ dày khung của TextField
                                anchors.fill: parent
                            }
        }
    }

    Text {
        width: 200
        height: 50
        anchors.horizontalCenter: parent.horizontalCenter
        y: 210
        text: qsTr("Log in to Oryza Cloud")
        font.pixelSize: 24
        color: "White"
    }

    Text {
        width: 200
        height: 50
        x: 40
        y: 420
        text: qsTr("Email")
        font.pixelSize: 18
        color: "#8E989C"
    }

    Rectangle {
        id : rec
        width: 130
        height: 40
        color: "#30A0DA"
        x: 270
        y: 580

        Rectangle {
            anchors.verticalCenter: parent.verticalCenter
            //anchors.topMargin:
            Text {

                //anchors.centerIn: parent
                text: qsTr("Next")
                font.pixelSize: 18
                color: "white"
            }

            Image {
                source: "qrc:/simple_arrow_h_right.png"
                height: 30
                width: 30

//                anchors.verticalCenter: parent.verticalCenter
//                anchors.right: parent.right
//                anchors.rightMargin: 10
                fillMode: Image.PreserveAspectFit  // Đảm bảo hình ảnh không bị méo khi thay đổi kích thước
            }
        }

    }

}


