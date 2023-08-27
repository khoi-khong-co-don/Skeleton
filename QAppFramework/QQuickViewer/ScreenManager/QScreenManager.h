#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include <QObject>
#include <QQmlEngine>
#include <QQuickItem>
#include <QQmlContext>

#include "QAppFramework.h"
#include "QScreenQueue.h"

class QScreenManager : public QObject
{
public:
    explicit QScreenManager(QQuickItem* rootObject, QQmlContext* context, uchar scr);
    virtual ~QScreenManager();

    bool showScreen(const APPLICATION_STATE *scr, QVariant msg = QVariant());
    uchar getCurrentScreen() const;
private:
    // It's static so it can be shared with all instances.
    // Since both views are sharing the QQmlEngine we can simply reuse the QQmlComponents.
    // The Loader will set the correct QQmlContext on them, so they see the properties for the view
    // they are in.
    static QScreenQueue cacheScreen;
    QQuickItem          *m_rootObject;
    QQmlContext         *m_context;
    uchar               m_screen;
    const APPLICATION_STATE *m_CurrentScreen;

private:
    QQmlComponentPtr getComponent(QObject *parent, QString screenFile);
};

#endif // SCREENMANAGER_H
