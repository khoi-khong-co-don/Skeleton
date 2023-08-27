QT += core qml gui quick widgets xml
CONFIG += c++11

# Required for QAppFramework.
include(QAppFramework/QAppFramework.pri)
include(QAppFramework/QDeployment.pri)
include(Views/Views.pri)

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += PROJECT_PATH=\"\\\"$${_PRO_FILE_PWD_}/\\\"\"

# To used the 3rd debuger such as dlt
DEFINES += USE_3RD_DEBUG

# Add more folders to ship with the application, here


# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# IncludePath

INCLUDEPATH += src/controller \
    src/model

RESOURCES += DataHMI/DataHMI.qrc \
    DataHMI/Images_2.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SOURCES += main.cpp \
    appengine.cpp \
    src/controller/controller.cpp \
    src/controller/editservercontroller.cpp \
    src/model/editservermodel.cpp \
    src/model/mainmodelserver.cpp \
    xmlreader.cpp

win32 : {
#    message("Build for WIN32" $$OUT_PWD)
    folder_01.source = $$PWD/DataHMI
    folder_01.target = $$OUT_PWD
    DEFINES += DEF_TRANSITION_ANIMATION_TYPE_1
    DEPLOYMENTFOLDERS += folder_01
}

qtcAddDeployment()

DISTFILES += \
    DataHMI/Qml/Images/arrow_left.png \
    modelServer.xml

HEADERS += \
    appengine.h \
    src/controller/controller.h \
    src/controller/editservercontroller.h \
    src/model/editservermodel.h \
    src/model/mainmodelserver.h \
    xmlreader.h
