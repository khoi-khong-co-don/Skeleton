import QtQuick 2.15

Item {
    property ListModel listModel: ListModel {
        ListElement {
            name: "KHOI KHAU KHINH"
            server: "192.168.111.65:7001"
            username: "admin"
            password: "oryza@2023"
            connect: "true"
            login: "true"
        }
        ListElement {
            name: "TAN"
            server: "192.168.111.65:7001"
            username: "admin"
            password: "oryza@2023"
            connect: "false"
            login: "true"
        }
        ListElement {
            name: "Oryza-VMS"
            server: "192.168.111.65:7001"
            username: "admin"
            password: "oryza@2023"
            connect: "true"
            login: "false"
        }
        ListElement {
            name: "oryza-H610M"
            server: "192.168.111.65:7001"
            username: "admin"
            connect: "true"
            login: "false"
        }
        ListElement {
            name: "new1"
            server: "192.168.111.65:7001"
            username: "admin"
            password: "oryza@2023"
            connect: "true"
            login: "false"
        }
        ListElement {
            name: "new2"
            server: "192.168.111.65:7001"
            username: "admin"
            password: "oryza@2023"
            connect: "false"
            login: "false"
        }
        ListElement {
            name: "new3"
            server: "192.168.111.65:7001"
            username: "admin"
            password: "oryza@2023"
            connect: "false"
            login: "false"
        }
        ListElement {
            name: "new4"
            server: "192.168.111.65:7001"
            username: "admin"
            password: "oryza@2023"
            login: "false"
        }
        ListElement {
            name: "new5"
            server: "192.168.111.65:7001"
            username: "admin"
            password: "oryza@2023"
            connect: "false"
            login: "false"
        }
    }
}
