#ifndef QQUICKVIEWER_H
#define QQUICKVIEWER_H

#include <QObject>
#include <QGuiApplication>
#include <QQuickView>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQmlComponent>

#include "QAppFramework.h"

class QQuickViewer : public QObject
{
    Q_OBJECT
private:

    explicit QQuickViewer(uchar scr);

public:
    virtual ~QQuickViewer();

    static QQuickViewer *getInstance(uchar scr);
    /* <Function>
     *  initialized()
     * <Desciption>
     *  Initial viewer of application
     * <Params>
     *  NONE
     * <Return>
     *  NONE
     * <Author>
     *  ThanhNV22
     */
    void initialized();

    /* <Function>
     *  completed()
     * <Desciption>
     *  Complete the init section of viewer of application. Call this function after initial and register context property
     * <Params>
     *  NONE
     * <Return>
     *  NONE
     * <Author>
     *  ThanhNV22
     */
    void completed();

    /* <Function>
     *  void registerContextProperty(const QString &str, const QVariant &var)
     * <Desciption>
     *  Register the context property for QML context, this shoud be call before completed()
     * <Params>
     *  str : Name of property
     *  var : Value of property
     * <Return>
     *  true : Property register succeed
     *  false: Property register already existed
     * <Author>
     *  ThanhNV22
     */
    Q_INVOKABLE void registerContextProperty(const QString &str, const QVariant &var);

    /* <Function>
     *  QList<QString> contextPropertiesRegisted()
     * <Desciption>
     *  Return the list of properties are registered with viewer context
     * <Params>
     *  NONE
     * <Return>
     *  The list of properties are registered with viewer context
     * <Author>
     *  ThanhNV22
     */
    QList<QString> contextPropertiesRegisted() const;

    /* <Function>
     *  bool updateContextProperty(const QString &str, const QVariant &var)
     * <Desciption>
     *  Update value of the context property which is registered
     * <Params>
     *  str : Name of property
     *  var : Value of property
     * <Return>
     *  true : Value of property update succeed
     *  false: Value of property update failure
     * <Author>
     *  ThanhNV22
     */
    bool updateContextProperty(const QString &str, const QVariant &var);

    /* <Function>
     *  void sendEvent(uchar eventID, QVariant msg = QVariant())
     * <Desciption>
     *  Send event from user request. This funtion able to call from qml
     * <Params>
     *  eventID : Event ID, defined by user
     *  msg     : Message of event
     * <Return>
     *  NONE
     * <Author>
     *  ThanhNV22
     */
    Q_INVOKABLE void sendEvent(uchar eventID, QVariant msg = QVariant());

    /* <Function>
     *  void doRegisterQML(QObject* obj)
     * <Desciption>
     *  Register qml to manage order index
     * <Params>
     *  Obj     : Object of qml
     * <Return>
     *  NONE
     * <Author>
     *  ThanhNV22
     */
    Q_INVOKABLE void doRegisterQML(QObject* objPropose);

    /* <Function>
     *  void unRegisterQML(QObject* obj)
     * <Desciption>
     *  Unregister qml to manage order index
     * <Params>
     *  Obj     : Object of qml
     * <Return>
     *  NONE
     * <Author>
     *  ThanhNV22
     */
    Q_INVOKABLE void unRegisterQML(QObject* objPropose);

    /* <Function>
     *  bool setViewerSize(int width, int height)
     * <Desciption>
     *  Set window size
     * <Params>
     *  width : Width of window
     *  height: Height of window
     * <Return>
     *  true/false: succeed/false
     * <Author>
     *  ThanhNV22
     */
    bool setViewerSize(int width, int height);

    /* <Function>
     *  bool show()
     * <Desciption>
     *  Shows the window
     * <Params>
     *  NONE
     * <Return>
     *  true : Show window succeed
     *  false: Could not show window
     * <Author>
     *  ThanhNV22
     */
    bool show();

    /* <Function>
     *  bool hide()
     * <Desciption>
     *  Hide the window
     * <Params>
     *  NONE
     * <Return>
     *  true : Hide window succeed
     *  false: Could not Hide window
     * <Author>
     *  ThanhNV22
     */
    bool hide();

    /* <Function>
     *  QQmlContext *getContext()
     * <Desciption>
     *  Get qml Context
     * <Params>
     *  NONE
     * <Return>
     *  Return the QQmlContext
     * <Author>
     *  ThanhNV22
     */
    QQmlContext *getQmlContext() const;

    /* <Function>
     *  QQuickView *getWindow()
     * <Desciption>
     *  Get Window viewer
     * <Params>
     *  NONE
     * <Return>
     *  Return the QQuickView
     * <Author>
     *  ThanhNV22
     */
    QQuickView *getQuickWindow() const;

    /* <Function>
     *  QList<uchar> getCurrentStates() const
     * <Desciption>
     *  Get Current states are showing on viewer
     * <Params>
     *  NONE
     * <Return>
     *  Return the List of ID states are showing
     * <Author>
     *  ThanhNV22
     */
    QList<uchar> getCurrentStates() const;

    /* <Function>
     *  void registerStates(const st_STATE_REGISTER tbl[], const unsigned int count)
     * <Desciption>
     *  Static function, Request register all of states define by user
     * <Params>
     *  tbl     : Table of states, define with struct st_STATE_REGISTER
     *  count   : Size of table
     * <Return>
     *  NONE
     * <Author>
     *  ThanhNV22
     */
    static void registerStates(const STATE_SYSTEM tbl[], uint len);

    /* <Function>
     *  QQuickViewer* instance(uchar scr)
     * <Desciption>
     *  Static function, get windows which are registered
     * <Params>
     *  scr     : From window index(such as 1/2/3/4 defined by VIEWER_INDEX)
     *  count   : Size of table
     * <Return>
     *  Return instance of QQuickViewer
     * <Author>
     *  ThanhNV22
     */
    static QQuickViewer* instance(uchar scr);

private:
    // It's static so it can be shared with all instances.
    // Since both views are sharing the QQmlEngine we can simply reuse the QQmlComponents.
    // The Loader will set the correct QQmlContext on them, so they see the properties for the view
    // they are in.
    static QQmlEngine                                   *m_qmlEngine;
    static bool                                         m_register;
    static QHash<uchar, QQuickViewer*>                  m_viewerRegisted;
    static QHash<uchar, const APPLICATION_STATE*>       m_stateRegisted;
    static QHash<uchar, QHash<uchar, STATE_TRIGGER> >   m_poolEvt;
    static QQuickViewer                                 *m_instance;
    QQuickView                                          *m_viewer;
    QQmlContext                                         *m_context;
    QQuickItem                                          *m_rootObject;
    uchar                                               m_screen;
    QScreenManager                                      *m_scrMng;
    QPopupManager                                       *m_popMng;
    QList<QString>                                      m_ctxProperties;
    uchar                                               m_RootState;
    QList<QObject*>                                     m_qmlObj;
private:
    /* <Function>
     *  QQuickItem* loadQml(QQuickView *view, const QUrl &url, QQmlContext *context)
     * <Desciption>
     *  Load main qml and return QQuickItem
     * <Params>
     *  view    : Window contains main qml
     *  url     : url of main qml
     *  context : Context of qml
     * <Return>
     *  Return QQuickItem
     * <Author>
     *  ThanhNV22
     */
    QQuickItem* loadQml(QQuickView *view, const QUrl &url, QQmlContext *context);

    /* <Function>
     *  void handleTransition(const APPLICATION_STATE *from, const APPLICATION_STATE *to, QVariant msg = QVariant())
     * <Desciption>
     *  Handle change state
     * <Params>
     *  from    : State is requester
     *  to      : State is target
     *  msg     : Message of event
     * <Return>
     *  NONE
     * <Author>
     *  ThanhNV22
     */
    void handleTransition(const APPLICATION_STATE *from, const APPLICATION_STATE *to, QVariant msg = QVariant());

    /* <Function>
     *  bool showScreen(uchar id, QVariant msg = QVariant())
     * <Desciption>
     *  Request show screen with ID
     * <Params>
     *  id  : State ID, defined by user
     *  msg : Message of event
     * <Return>
     *  Return true/false
     * <Author>
     *  ThanhNV22
     */
    bool showScreen(uchar id, QVariant msg = QVariant());

    /* <Function>
     *  bool showPopup(uchar id, QVariant msg = QVariant())
     * <Desciption>
     *  Request show popup with ID
     * <Params>
     *  id  : State ID, defined by user
     *  msg : Message of event
     * <Return>
     *  Return true/false
     * <Author>
     *  ThanhNV22
     */
    bool showPopup(uchar id, QVariant msg = QVariant());

    /* <Function>
     *  bool closePopup(uchar id, QVariant msg = QVariant())
     * <Desciption>
     *  Request close popup with ID
     * <Params>
     *  id  : State ID, defined by user
     *  msg : Message of event
     * <Return>
     *  Return true/false
     * <Author>
     *  ThanhNV22
     */
    bool closePopup(uchar id, QVariant msg = QVariant());

    /* <Function>
     *  closeAllPopup()
     * <Desciption>
     *  Request close all popup
     * <Params>
     *  NONE
     * <Return>
     *  Return true/false
     * <Author>
     *  ThanhNV22
     */
    bool closeAllPopup();

    /* <Function>
     *  collectGarbage()
     * <Desciption>
     *  Request collect garbage in JSEngine
     * <Params>
     *  NONE
     * <Return>
     *  NONE
     * <Author>
     *  ThanhNV22
     */
    void collectGarbage();
signals:
    /* <Function>
     *  void visibleChanged(bool state)
     * <Desciption>
     *  Signal notify window is visible changed
     * <Params>
     *  state    : State of window
     * <Return>
     *  NONE
     * <Author>
     *  ThanhNV22
     */
    void visibleChanged(bool state);

    /* <Function>
     *  void eventReceiver(int event, int data)
     * <Desciption>
     *  Signal notify event from C++
     * <Params>
     *  event    : Event ID
     *  data     : Data paired with event
     * <Return>
     *  NONE
     * <Author>
     *  ThanhNV22
     */
    void eventReceiver(int event, int data);

public slots:
    /* <Function>
     *  void onVisibleChanged(bool state)
     * <Desciption>
     *  Slot recived notification window is visible changed
     * <Params>
     *  state    : State of window
     * <Return>
     *  NONE
     * <Author>
     *  ThanhNV22
     */
    void onVisibleChanged(bool state);
};

#endif // QQUICKVIEWER_H
