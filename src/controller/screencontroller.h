#ifndef SCREENCONTROLLER_H
#define SCREENCONTROLLER_H

#include <QStack>
#include <QObject>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include "QQuickViewer.h"
class ScreenController : public QObject
{
    Q_OBJECT
private:
    explicit ScreenController(QObject *parent = nullptr);
public:
    ~ScreenController();

    // singleton pattern
    static ScreenController *getInstance();

    // initialize controller
    void initialize(QQmlContext *context);
    void initializeScreen(QQmlApplicationEngine *engine);

private:
    static ScreenController *m_instance;
    bool m_initialized;
    QQmlApplicationEngine *m_engine;
};

#endif // SCREENCONTROLLER_H
