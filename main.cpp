#include <QApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QtQuick>
#include "Views.h"
#include "appengine.h"

int main(int argc, char *argv[])
{/*
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);


    QQuickViewer::registerStates(STATE_ALL, ALEN(STATE_ALL));
    qmlRegisterType<E>("HMIEVENTS", 1, 0, "EVT");

    MainModelServer mainModelServer;
    Controller controller;
    controller.loadDataFromModel();

    QObject::connect(&mainModelServer, SIGNAL(sendMsg(QString)), &controller, SLOT(receMsg(QString)) );

    EditServerModel ediServerModel;
    EditServerController editServerController;
    editServerController.loadDataFromModel(&ediServerModel);

    QQuickViewer* viewer1 = new QQuickViewer((uchar)VIEWER_INDEX::VIEWER_1ST);
    viewer1->initialized();
    viewer1->registerContextProperty("ThanhNV22", 15);
    viewer1->registerContextProperty("mainModelServer", QVariant::fromValue(&mainModelServer));
    viewer1->registerContextProperty("editServer", QVariant::fromValue(&ediServerModel));



    viewer1->completed();
    viewer1->sendEvent(E::EVT_BLK_TO_SCREEN_B, "4");
    viewer1->show();*/
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    AppEngine::getInstance()->initialize(&app);


    return app.exec();
}
