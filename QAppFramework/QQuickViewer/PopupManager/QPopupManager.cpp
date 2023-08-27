#include "QPopupManager.h"

QPopupManager::QPopupManager(QQuickItem *rootObject, QQmlContext *context, uchar scr): m_screen(scr), m_rootObject(rootObject), m_context(context)
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    if(!m_listPopup.isEmpty()){
        m_listPopup.clear();
    }
    if(!m_QmlOder.isEmpty()){
        m_QmlOder.clear();
    }
}

QPopupManager::~QPopupManager()
{

}

QList<uchar> QPopupManager::getCurrentPopups() const
{
    QList<uchar> list;
    for (int i = 0; i < m_listPopup.count(); i++) {
        list.append(m_listPopup.at(i).data()->popupInfo().id);
    }
    return list;
}

bool QPopupManager::showPopup(POPUP_DATA p)
{
    int cIdx = -1;
    bool existed = false;
    for (int i = 0; i < m_listPopup.count(); i++)
    {
        if(p.id == m_listPopup.at(i).data()->popupInfo().id){
            cIdx = i;
            existed = true;
            break;
        }
    }

    if(!existed){
        PopupObjectPtr popup = PopupObjectPtr(new PopupObject(p, this->m_screen));
        m_listPopup.append(popup);
        if(LIMIT::NONE != popup.data()->popupInfo().duration){
            popup.data()->start((int)p.duration);
        }
        QObject::connect(popup.data() , SIGNAL(closePopupTimeout(uchar)),this, SLOT(onClosePopupTimeout(uchar)), Qt::QueuedConnection);
    }
    else{
        if(cIdx != (m_listPopup.count() - 1)){
            m_listPopup.move(cIdx, m_listPopup.count() - 1);
        }

        m_listPopup.last().data()->start((int)p.duration);
    }

    // SHOW QML
    qmlSyncup();
    if((NULL != p.funcEntry) && !existed){
        p.funcEntry(p.msg, this->m_screen);
    }
    return true;
}

bool QPopupManager::closePopup(POPUP_DATA p)
{
    bool ret = false;
    for (int i = 0; i < m_listPopup.count(); i++) {
        if(p.id == m_listPopup.at(i).data()->popupInfo().id){
            if(m_listPopup.at(i).data()->isActive()){
                m_listPopup.at(i).data()->stop();
            }
            ret = true;
            m_listPopup.at(i).data()->closePopupTimeout(m_listPopup.at(i).data()->popupInfo().id);
        }
    }
    return ret;
}

bool QPopupManager::closeAll()
{
    for (int i = 0; i < m_listPopup.count(); i++) {
        if(m_listPopup.at(i).data()->isActive()){
            m_listPopup.at(i).data()->stop();
        }
        m_listPopup.at(i).data()->closePopupTimeout(m_listPopup.at(i).data()->popupInfo().id);
    }
    m_listPopup.clear();
    return m_listPopup.isEmpty();
}

void QPopupManager::qmlSyncup()
{
    QStringList m_PopupQmlData;
    m_PopupQmlData.clear();

    for (int i = 0; i < m_listPopup.count(); i++) {
        m_PopupQmlData << m_listPopup.at(i).data()->popupInfo().QmlPath;
    }

    if(m_QmlOder != m_PopupQmlData){
        m_QmlOder.clear();
        m_QmlOder = m_PopupQmlData;
        QMetaObject::invokeMethod(m_rootObject, JS_POPUPS_TRANSITION_FUNCTION, Q_ARG(QVariant, QVariant::fromValue(m_QmlOder)), Q_ARG(QVariant,QVariant::fromValue( m_QmlOder.count())));
    }
    m_PopupQmlData.clear();
}

void QPopupManager::onClosePopupTimeout(uchar id)
{
    QMutableListIterator<PopupObjectPtr> i(m_listPopup);
    while (i.hasNext()) {
        PopupObjectPtr bs = i.next();
        if(id == bs.data()->popupInfo().id){
            i.remove();
        }
    }
    qmlSyncup();
}

PopupObject::PopupObject(POPUP_DATA p, uchar screen): m_popInfo(p), m_screen(screen)
{
    if(LIMIT::NONE != p.duration){
        QObject::connect(this , SIGNAL(timeout()),this, SLOT(timeout_exec()));
    }
}

PopupObject::~PopupObject()
{
    if(NULL != m_popInfo.funcEntry){
        m_popInfo.funcExit(m_popInfo.msg, this->m_screen);
    }
}

POPUP_DATA PopupObject::popupInfo() const
{
    return m_popInfo;
}

void PopupObject::timeout_exec()
{
    this->stop();
    emit closePopupTimeout(m_popInfo.id);
}
