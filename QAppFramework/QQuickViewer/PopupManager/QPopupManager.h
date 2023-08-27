#ifndef QPOPUPMANAGER_H
#define QPOPUPMANAGER_H

#include <QObject>
#include <QStack>
#include <QSharedPointer>
#include <QTimer>
#include <QQmlEngine>
#include <QQuickItem>
#include <QQmlContext>
#include "QAppFramework.h"

class PopupObject;
class QPopupManager;
typedef QSharedPointer<PopupObject> PopupObjectPtr;

class QPopupManager : public QObject
{
    Q_OBJECT
public:
    explicit QPopupManager(QQuickItem* rootObject, QQmlContext* context, uchar scr);
    virtual ~QPopupManager();
    QList<uchar> getCurrentPopups() const;
    bool showPopup(POPUP_DATA p);
    bool closePopup(POPUP_DATA p);
    bool closeAll();
private:
    uchar                   m_screen;
    QQuickItem              *m_rootObject;
    QQmlContext             *m_context;
    QList<PopupObjectPtr>   m_listPopup;
    QStringList             m_QmlOder;
    void qmlSyncup();

public slots:
    void onClosePopupTimeout(uchar id);
};

class PopupObject: public QTimer
{
    Q_OBJECT
public:
    explicit PopupObject(POPUP_DATA p, uchar screen);
    virtual ~PopupObject();
    POPUP_DATA popupInfo() const;
private:
    POPUP_DATA   m_popInfo;
    uchar        m_screen;
signals:
    void closePopupTimeout(uchar id);
public slots:
    void timeout_exec();
};


#endif // QPOPUPMANAGER_H
