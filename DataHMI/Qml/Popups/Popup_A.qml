  //Common.QRootScreen {
//    Rectangle {
//        width: 600
//        height: 300
//        anchors.centerIn: parent
//        color: "Pink"
//        Row {
//            anchors.bottom: parent.bottom
//            spacing: 10
//            Rectangle {
//                width: 100
//                height: 50
//                border.color: "Black"
//                Text {
//                    text: qsTr("Popup_A_XXX")
//                }
//                MouseArea {
//                    anchors.fill: parent
//                    onClicked: {
//                        QMLHandle.sendEvent(EVT.EVT_POPUP_A_BUTTON_XXX_CLICKED)
//                    }
//                }
//            }
//            Rectangle {
//                width: 100
//                height: 50
//                border.color: "Black"
//                Text {
//                    text: qsTr("Popup_A_YYY")
//                }
//                MouseArea {
//                    anchors.fill: parent
//                    onClicked: {
//                        QMLHandle.sendEvent(EVT.EVT_POPUP_A_BUTTON_YYY_CLICKED)
//                    }
//                }
//            }
//        }
//    }
//}



import QtQuick 2.0
import QtQuick.Controls 2.0
import HMIEVENTS 1.0
import "./../../../QAppFramework/QQml/Common" as Common

Common.QRootScreen {
    Rectangle {anchors.fill: parent; color: "Black"}

    Row {
        anchors.horizontalCenter: parent.horizontalCenter  // Center the row horizontally
        y: 400
        spacing: 5

        Rectangle {
            width: 400
            height: 40
            color: "#87CEEB"  // Set the background color to gray
            border.color: "#87CEEB"
            radius: 5  // Add rounded corners to the rectangle
            // Center the rectangle horizontally
            anchors.horizontalCenter: parent.horizontalCenter
            // Position the bottom of the rectangle at the bottom of its parent
            Text {
                text: qsTr("Connect")
                color: "white"
                anchors.centerIn: parent  // Center the text both vertically and horizontally
                horizontalAlignment: Text.AlignHCenter  // Center the text horizontally
                verticalAlignment: Text.AlignVCenter  // Center the text vertically
            }
        }
    }

    Row {
        anchors.top: parent.top  // Position the top of the row at the top of its parent
        anchors.left: parent.left  // Position the right side of the row at the right side of its parent
        spacing: 5
        Text {
                width: 150
                height: 40
                text: qsTr("Connect to Server")
                color: "white"
                horizontalAlignment: Text.AlignHCenter  // Center the text horizontally
                verticalAlignment: Text.AlignVCenter  // Center the text vertically
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    QMLHandle.sendEvent(EVT.EVT_SCREEN_B_BUTTON_YYY_CLICKED)
                }
            }
        }
    }

    Row {
        anchors.horizontalCenter: parent.horizontalCenter  // Center the row horizontally
        y: 100
        spacing: 5

        TextField {
                width: 400
                height: 40
                placeholderText: qsTr("Enter Host port")  // Placeholder text when the field is empty
                color: "black"
                selectionColor: "lightblue"  // Color of the selected text
                cursorVisible: true  // Show the text cursor
                selectByMouse: true   // Allow text selection using the mouse
                text: qsTr("Host:Port")
                horizontalAlignment: Text.AlignLeft  // Center the text horizontally
                verticalAlignment: Text.AlignVCenter  // Center the text vertically
        }
    }

    Row {
        anchors.horizontalCenter: parent.horizontalCenter  // Center the row horizontally
        y: 200
        spacing: 5

        TextField {
                width: 400
                height: 40
                placeholderText: qsTr("Enter username")  // Placeholder text when the field is empty
                color: "black"
                selectionColor: "lightblue"  // Color of the selected text
                cursorVisible: true  // Show the text cursor
                selectByMouse: true   // Allow text selection using the mouse
                text: qsTr("Login")
                horizontalAlignment: Text.AlignLeft  // Center the text horizontally
                verticalAlignment: Text.AlignVCenter  // Center the text vertically
        }
    }

    Row {
        anchors.horizontalCenter: parent.horizontalCenter  // Center the row horizontally
        y: 300
        spacing: 5

        TextField  {
                width: 400
                height: 40
                placeholderText: qsTr("Enter password")  // Placeholder text when the field is empty
                color: "black"
                selectionColor: "lightblue"  // Color of the selected text
                cursorVisible: false  // Show the text cursor
                selectByMouse: true   // Allow text selection using the mouse
                text: qsTr("Password")
                horizontalAlignment: Text.AlignLeft  // Center the text horizontally
                verticalAlignment: Text.AlignVCenter  // Center the text vertically
        }
    }
}
