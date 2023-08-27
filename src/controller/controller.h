#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <xmlreader.h>
#include "mainmodelserver.h"
#include <QDebug>
#include <QQmlContext>
#include "QQuickViewer.h"
class Controller : public QObject
{
    Q_OBJECT

private:
    explicit Controller(QObject *parent = nullptr);

public:

    ~Controller();

    //singleton patten
    static Controller *getInstance();

    //initializa controller
    void initialize(QQuickViewer *view);
    void loadDataFromModel();

public slots:
    void receMsg(const QString &msg);

private:
    static Controller *m_instance;
    bool m_initialize;
    MainModelServer m_model;
    XmlReader m_xmlReader;
};

#endif // CONTROLLER_H
