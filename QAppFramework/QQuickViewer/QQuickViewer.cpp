#include "QQuickViewer.h"
#include "QOutlog.h"
#include <QScreen>
#include <QApplication>
QQmlEngine* QQuickViewer::m_qmlEngine   = NULL;
bool        QQuickViewer::m_register    = false;
QHash<uchar, QQuickViewer*>                 QQuickViewer::m_viewerRegisted;
QHash<uchar, const APPLICATION_STATE*>      QQuickViewer::m_stateRegisted;
QHash<uchar, QHash<uchar, STATE_TRIGGER> >  QQuickViewer::m_poolEvt;
QQuickViewer* QQuickViewer::m_instance  = NULL;

QQuickViewer::QQuickViewer(uchar scr) : m_viewer(NULL), m_context(NULL), m_rootObject(NULL), m_screen(scr), m_scrMng(NULL), m_popMng(NULL), m_RootState(0)
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

QQuickViewer::~QQuickViewer()
{
    safeDelete(m_viewer);
    safeDelete(m_context);
    safeDelete(m_rootObject);
    safeDelete(m_scrMng);
}

QQuickViewer *QQuickViewer::getInstance(uchar scr)
{
    if(m_instance == nullptr)
    {
        m_instance = new QQuickViewer(scr);
        qDebug() <<QString::number(reinterpret_cast<quintptr>(m_instance), 16);
    }

    return m_instance;
}

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
void QQuickViewer::initialized()
{
    if(NULL == m_qmlEngine){
        m_qmlEngine = new QQmlEngine();
    }
    m_viewer = new QQuickView(m_qmlEngine, nullptr);
    m_context = new QQmlContext(m_viewer->rootContext());
    QObject::connect(m_viewer, SIGNAL(visibleChanged(bool)), this, SIGNAL(visibleChanged(bool)));
    QObject::connect(m_viewer, SIGNAL(visibleChanged(bool)), this, SLOT(onVisibleChanged(bool)));
    m_ctxProperties.clear();
    m_qmlObj.clear();
    this->registerContextProperty("QAPP_VIEWER_INDEX", QVariant::fromValue(m_screen));
    this->registerContextProperty("QAPP_DEVICE_WIDTH", 0);
    this->registerContextProperty("QAPP_DEVICE_HEIGHT", 0);
    this->registerContextProperty("QMLHandle", QVariant::fromValue(this));
    //this->setViewerSize(390, 732);
    QScreen *screen = QApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int deviceWidth = screenGeometry.width();
    int deviceHeight = screenGeometry.height();


    this->setViewerSize(deviceWidth, deviceHeight-20);
}

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
void QQuickViewer::completed()
{
#if   DEF_TRANSITION_ANIMATION_TYPE_1
    m_rootObject = loadQml(m_viewer, QUrl(QStringLiteral(MAIN_VIEWPORT_ANIMATION1_QML)), m_context);
#elif DEF_TRANSITION_ANIMATION_TYPE_2
    m_rootObject = loadQml(m_viewer, QUrl(QStringLiteral(MAIN_VIEWPORT_ANIMATION2_QML)), m_context);
#else
    m_rootObject = loadQml(m_viewer, QUrl(QStringLiteral(MAIN_VIEWPORT_QML)), m_context);
#endif
    m_scrMng = new QScreenManager(m_rootObject, m_context, m_screen);
    m_popMng = new QPopupManager(m_rootObject, m_context, m_screen);
    m_viewerRegisted[m_screen] = this;

    for (int i = 0; i < m_stateRegisted.keys().count(); i++) {
        if(LAYER::LAYER_BASE == m_stateRegisted[m_stateRegisted.keys().at(i)]->layerbase){
            m_RootState = m_stateRegisted[m_stateRegisted.keys().at(i)]->id;
            break;
        }
    }
}

/* <Function>
 *  bool registerContextProperty(const QString &str, const QVariant &var)
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
void QQuickViewer::registerContextProperty(const QString &str, const QVariant &var)
{
    if(m_ctxProperties.contains(str)){
        DBG_ERROR << "Property " << str << "Already existed";
       // return false;
    }
    m_ctxProperties.append(str);
    if(NULL != m_context){
        m_context->setContextProperty(str, var);
    }
    //return true;
}

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
QList<QString> QQuickViewer::contextPropertiesRegisted() const
{
    return m_ctxProperties;
}

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
bool QQuickViewer::updateContextProperty(const QString &str, const QVariant &var)
{
    bool ret = false;
    if(m_ctxProperties.contains(str) && (NULL != m_context)){
        m_context->setContextProperty(str, var);
        ret = true;
    }
    else{
        DBG_WARN << "The property" << str << "Did not initial, it should be register with registerContextProperty() before call completed()";
    }
    return ret;
}

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
void QQuickViewer::sendEvent(uchar eventID, QVariant msg)
{
    DBG_INFO << eventID;
    // CHECK IN CURRENT POPUP
    if(NULL != m_popMng){
        QList<uchar> pops = m_popMng->getCurrentPopups();
        for (int i = 0; i < pops.count(); i++) {
            if(m_poolEvt[pops.at(i)].contains(eventID)){
                if(NULL != m_poolEvt[pops.at(i)][eventID].func){
                    m_poolEvt[pops.at(i)][eventID].func(msg, m_screen);
                }

                if(NULL != m_poolEvt[pops.at(i)][eventID].trans){
                    handleTransition(m_stateRegisted[pops.at(i)], m_poolEvt[pops.at(i)][eventID].trans, msg);
                }
                return;
            }
        }
    }

    // CHECK IN CURRENT SCREEN
    if(NULL != m_scrMng){
        uchar scr = m_scrMng->getCurrentScreen();
        if(m_poolEvt[scr].contains(eventID)){
            if(NULL != m_poolEvt[scr][eventID].func){
                m_poolEvt[scr][eventID].func(msg, m_screen);
            }

            if(NULL != m_poolEvt[scr][eventID].trans){
                handleTransition(m_stateRegisted[scr], m_poolEvt[scr][eventID].trans, msg);
            }
            return;
        }
    }

    // CHECK IN ROOT
    if(m_poolEvt[m_RootState].contains(eventID)){
        if(NULL != m_poolEvt[m_RootState][eventID].func){
            m_poolEvt[m_RootState][eventID].func(msg, m_screen);
        }

        if(NULL != m_poolEvt[m_RootState][eventID].trans){
            handleTransition(m_stateRegisted[m_RootState], m_poolEvt[m_RootState][eventID].trans, msg);
        }
        return;
    }

}

/* <Function>
 *  void doRegisterQML(QObject* objPropose)
 * <Desciption>
 *  Register qml to manage order index
 * <Params>
 *  Obj     : Object of qml
 * <Return>
 *  NONE
 * <Author>
 *  ThanhNV22
 */
void QQuickViewer::doRegisterQML(QObject *objPropose)
{
    m_qmlObj.insert(0, objPropose);
    for (QObject* obj: m_qmlObj) {
        if( m_qmlObj.first() == obj){
            obj->setProperty("isOnTop", true);
            QObject::connect(this, SIGNAL(eventReceiver(int,int)), obj, SIGNAL(eventReceiver(int, int)));
        }
        else{
            obj->setProperty("isOnTop", false);
            this->disconnect(obj);
        }
    }
    DBG_INFO << m_qmlObj;
}

/* <Function>
 *  void unRegisterQML(QObject* objPropose)
 * <Desciption>
 *  Unregister qml to manage order index
 * <Params>
 *  Obj     : Object of qml
 * <Return>
 *  NONE
 * <Author>
 *  ThanhNV22
 */
void QQuickViewer::unRegisterQML(QObject *objPropose)
{
    m_qmlObj.removeAll(objPropose);
    for (QObject* obj: m_qmlObj) {
        if( m_qmlObj.first() == obj){
            obj->setProperty("isOnTop", true);
            QObject::connect(this, SIGNAL(eventReceiver(int,int)), obj, SIGNAL(eventReceiver(int, int)));
        }
        else{
            obj->setProperty("isOnTop", false);
            this->disconnect(obj);
        }
    }
    DBG_INFO << m_qmlObj;
}

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
bool QQuickViewer::setViewerSize(int width, int height)
{
    bool ret = false;
    ret = this->updateContextProperty("QAPP_DEVICE_WIDTH", width);
    ret = this->updateContextProperty("QAPP_DEVICE_HEIGHT", height);
    return ret;
}

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
bool QQuickViewer::show()
{
    bool state = false;
    if(NULL != m_viewer){
        m_viewer->show();
        state = true;
    }
    return state;
}

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
bool QQuickViewer::hide()
{
    bool state = false;
    if(NULL != m_viewer){
        m_viewer->hide();
        state = true;
    }
    return state;
}

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
QQmlContext *QQuickViewer::getQmlContext() const
{
    return m_context;
}

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
QQuickView *QQuickViewer::getQuickWindow() const
{
    return m_viewer;
}

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
QList<uchar> QQuickViewer::getCurrentStates() const
{
    QList<uchar> list ;
    if(NULL != m_scrMng){
        list.append(m_scrMng->getCurrentScreen());
    }

    if(NULL != m_popMng){
        QList<uchar> tmp = m_popMng->getCurrentPopups();
        for (int j = 0; j < tmp.count(); ++j) {
            list.append(tmp.at(j));
        }
    }
    return list;
}

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
void QQuickViewer::registerStates(const STATE_SYSTEM tbl[], uint len)
{
    if(false == m_register){
        if(!m_poolEvt.isEmpty()){
            m_poolEvt.clear();
        }

        if(!m_stateRegisted.isEmpty()){
            m_stateRegisted.clear();
        }

        // Looking for all child
        for (uint i = 0; i < len; i++) {
            m_stateRegisted[tbl[i].id] = tbl[i].state;
            for (uint j = 0; j < tbl[i].size; j++) {
                m_poolEvt[tbl[i].id][tbl[i].trigger[j].evt] = tbl[i].trigger[j];
            }           
        }

        m_register = true;
        DBG_INFO << "THERE ARE " << m_stateRegisted.count() << "STATES REGISTED";
    }
}

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
QQuickViewer *QQuickViewer::instance(uchar scr)
{
    return m_viewerRegisted[scr];
}

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
QQuickItem* QQuickViewer::loadQml(QQuickView *view, const QUrl &url, QQmlContext *context)
{
    auto component = new QQmlComponent(view->engine(), url, view);
    if (component->isError()) {
        QList<QQmlError> errorList = component->errors();
        foreach (const QQmlError &error, errorList) {
            QMessageLogger(error.url().toString().toLatin1().constData(), error.line(), 0).warning() << error;
        }
        return NULL;
    }
    auto *obj = component->create(context);
    if (component->isError()) {
        QList<QQmlError> errorList = component->errors();
        foreach (const QQmlError &error, errorList) {
            QMessageLogger(error.url().toString().toLatin1().constData(), error.line(), 0).warning() << error;
        }
        return NULL;
    }
    view->setContent(url, component, obj);
    return view->rootObject();
}

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
void QQuickViewer::handleTransition(const APPLICATION_STATE *from, const APPLICATION_STATE *to, QVariant msg)
{
    if(((NULL != from) && (NULL != to))){
        if((LAYER::LAYER_POPUP == to->layerbase) || (LAYER::LAYER_TOAST == to->layerbase)){
            this->showPopup(to->id, msg);
        }
        else if(LAYER::LAYER_SCREEN == to->layerbase)
        {
            if((NULL != m_scrMng) && (to->id == m_scrMng->getCurrentScreen()) && (LAYER::LAYER_BASE != from->layerbase) && (LAYER::LAYER_SCREEN != from->layerbase)){
                this->closePopup(from->id, msg);
            }
            else{
                this->closeAllPopup();
                this->showScreen(to->id, msg);
            }
        }
        else{/*No handle*/}
    }
}

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
bool QQuickViewer::showScreen(uchar id, QVariant msg)
{
    bool ret = false;
    if((NULL != m_scrMng) && m_stateRegisted.contains(id)){
        if(LAYER::LAYER_SCREEN == m_stateRegisted[id]->layerbase){
            ret = m_scrMng->showScreen(m_stateRegisted[id], msg);
        }
    }
    return ret;
}

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
bool QQuickViewer::showPopup(uchar id, QVariant msg)
{
    bool ret = false;
    if((NULL != m_popMng) && m_stateRegisted.contains(id)){
        if((LAYER::LAYER_TOAST == m_stateRegisted[id]->layerbase) || (LAYER::LAYER_POPUP == m_stateRegisted[id]->layerbase))
        {
            POPUP_DATA pop;
            pop.duration    = m_stateRegisted[id]->duration;
            pop.id          = m_stateRegisted[id]->id;
            pop.QmlPath     = m_stateRegisted[id]->QmlPath;
            pop.funcEntry   = m_stateRegisted[id]->funcEntry;
            pop.funcExit    = m_stateRegisted[id]->funcExit;
            pop.msg         = msg;
            ret = m_popMng->showPopup(pop);
        }
    }
    return ret;
}

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
bool QQuickViewer::closePopup(uchar id, QVariant msg)
{
    bool ret = false;
    if((NULL != m_popMng) && m_stateRegisted.contains(id)){
        if((LAYER::LAYER_TOAST == m_stateRegisted[id]->layerbase) || (LAYER::LAYER_POPUP == m_stateRegisted[id]->layerbase))
        {
            POPUP_DATA pop;
            pop.duration    = m_stateRegisted[id]->duration;
            pop.id          = m_stateRegisted[id]->id;
            pop.QmlPath     = m_stateRegisted[id]->QmlPath;
            pop.funcEntry   = m_stateRegisted[id]->funcEntry;
            pop.funcExit    = m_stateRegisted[id]->funcExit;
            pop.msg         = msg;
            ret = m_popMng->closePopup(pop);
        }
    }
    return ret;
}

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
bool QQuickViewer::closeAllPopup()
{
    bool ret = false;
    if(NULL != m_popMng){
        ret = m_popMng->closeAll();
    }
    return ret;
}

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
void QQuickViewer::collectGarbage()
{
    if(NULL != m_qmlEngine){
        m_qmlEngine->collectGarbage();
    }
}

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
void QQuickViewer::onVisibleChanged(bool state)
{
    Q_UNUSED(state);
}
