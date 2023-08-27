#include "QScreenManager.h"

QScreenQueue QScreenManager::cacheScreen;
QScreenManager::QScreenManager(QQuickItem* rootObject, QQmlContext* context, uchar scr): m_rootObject(rootObject), m_context(context), m_screen(scr), m_CurrentScreen(NULL)
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

QScreenManager::~QScreenManager()
{

}

bool QScreenManager::showScreen(const APPLICATION_STATE *scr, QVariant msg)
{
    bool ret = false;
    if((NULL != m_rootObject) && (NULL != scr) && (m_CurrentScreen != scr)){
        QString path = scr->QmlPath;
        if(!cacheScreen.contains(path)){
            QQmlComponentPtr newComp = getComponent(m_rootObject, path);
            m_context->setContextProperty("QAppScreen", nullptr);
            m_context->setContextProperty("QAppScreen", newComp.data());
            cacheScreen.insert(path, newComp);
            newComp.clear();
        }
        else{
            m_context->setContextProperty("QAppScreen", nullptr);
            m_context->setContextProperty("QAppScreen", cacheScreen[path].data());
        }

        if(cacheScreen[path].data()->isError()){
            DBG_ERROR << "SCREEN_STATE ERROR:" << cacheScreen[path].data()->errors();
        }
        else{
            if(NULL != scr){
                scr->funcEntry(msg, m_screen);
            }
            ret = QMetaObject::invokeMethod(m_rootObject, JS_SCREEN_TRANSITION_FUNCTION/*, Qt::QueuedConnection*/);
            if(NULL != m_CurrentScreen){
                m_CurrentScreen->funcExit(msg, m_screen);
            }
            m_CurrentScreen = scr;
        }
    }
    return ret;
}

uchar QScreenManager::getCurrentScreen() const
{
    return (NULL != m_CurrentScreen) ? m_CurrentScreen->id : 0;
}

QQmlComponentPtr QScreenManager::getComponent(QObject *parent, QString screenFile) {
    if(NULL != parent){
        QQmlEngine *engine = qmlEngine(parent);
        if(engine) {
            QQmlComponentPtr component = QQmlComponentPtr(new QQmlComponent(engine, screenFile, this));
            QQmlEngine::setObjectOwnership(component.data(), QQmlEngine::CppOwnership);
            return component;
        }
    }
    return QQmlComponentPtr(NULL);
}

