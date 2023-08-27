#ifndef APPENGINE_H
#define APPENGINE_H

#include <QObject>
#include <QApplication>
#include <QQmlApplicationEngine>

#include "Views.h"
#include "controller.h"
#include "editservercontroller.h"

#include "QQuickViewer.h"
#include "screencontroller.h"
#include "editservercontroller.h"
#include "editservermodel.h"

class AppEngine : public QObject
{
    Q_OBJECT

private:
    explicit AppEngine(QObject *parent = nullptr);

public:
    ~AppEngine();

    // singleton pattern
    static AppEngine *getInstance();

    // initialize app
    void initialize(QApplication *app);

    EditServerModel *editModel();

private:
    void registerQmlObjects();
    void createControllers();
    void initControllers();
    void initScreens();

private:
    static AppEngine* m_instance;
    bool m_initialized;
    QApplication* m_app; // init GUI engine
    QQmlApplicationEngine m_engine; // registes QML type
    QQuickViewer *m_view;

};

#endif // APPENGINE_H
