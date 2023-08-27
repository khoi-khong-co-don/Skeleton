#include "editservercontroller.h"

EditServerController* EditServerController::m_instance = nullptr;

EditServerController::EditServerController(QObject *parent)
    : QObject(parent )
    ,m_initialize(false)
{
    qDebug() << __func__ << "START";
    loadDataFromModel();
    qDebug() << __func__ << "END";
}

EditServerController::~EditServerController()
{
    qDebug() << __func__ << "START";
    m_instance = nullptr;
    qDebug() << __func__ << "END";
}

EditServerController *EditServerController::getInstance()
{
    qDebug() << __func__ << "START";
    if( m_instance == nullptr)
    {
        m_instance = new EditServerController();
    }
    return m_instance;
    qDebug() << __func__ << "END";
}

EditServerModel *EditServerController::getInstanceModel()
{
    qDebug() <<__func__ << QString::number(reinterpret_cast<quintptr>(&m_model), 16);
    return &m_model;
}

void EditServerController::initialize(QQuickViewer *view)
{
    qDebug() << __func__ << "START";
    if(!m_initialize)
    {
        qDebug() <<__func__ << QString::number(reinterpret_cast<quintptr>(&m_model), 16);
        view->registerContextProperty("ediServerModel", QVariant::fromValue(&m_model));
    }
    qDebug() << __func__ << "END";
}

void EditServerController::loadDataFromModel()
{
    qDebug() << __func__ << "START";

//    m_xmlReader.ReadXmlFile("/storage/emulated/0/Download/modelServer.xml");
//    m_xmlReader.ParserXml(&m_model);
    qDebug() << __func__ << "END";
}
