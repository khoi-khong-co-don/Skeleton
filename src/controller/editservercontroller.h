#ifndef EDITSERVERCONTROLLER_H
#define EDITSERVERCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <xmlreader.h>
#include "QQuickViewer.h"
#include "editservermodel.h"
class EditServerController : public QObject
{
    Q_OBJECT
private:
    explicit EditServerController(QObject *parent = nullptr);
public:
    ~EditServerController();
    //singleton patten
    static EditServerController *getInstance();
    EditServerModel* getInstanceModel();
    //inittialize controller
    void initialize(QQuickViewer *view);
    void loadDataFromModel();

private:
    XmlReader m_xmlReader;
    static EditServerController *m_instance;
    bool m_initialize;
    EditServerModel m_model;
};

#endif // EDITSERVERCONTROLLER_H
