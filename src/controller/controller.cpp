#include "controller.h"

Controller* Controller::m_instance = nullptr;
Controller::Controller(QObject *parent)
    : QObject(parent )
    ,m_initialize(false)
{
    qDebug() << __func__ << "START";
    loadDataFromModel();
    qDebug() << __func__ << "END";
}

Controller::~Controller()
{
    qDebug() << __func__ << "START";
    m_instance = nullptr;
    qDebug() << __func__ << "END";
}

Controller *Controller::getInstance()
{
    qDebug() << __func__ << "START";
    if( m_instance == nullptr)
    {
        m_instance = new Controller();
    }
    return m_instance;
    qDebug() << __func__ << "END";
}

void Controller::initialize(QQuickViewer *view)
{
    qDebug() << __func__ << "START";
    if(!m_initialize)
    {
        qDebug() <<QString::number(reinterpret_cast<quintptr>(view), 16);
        view->registerContextProperty("mainModelServer", QVariant::fromValue(&m_model));
    }
    qDebug() << __func__ << "END";
}

void Controller::loadDataFromModel()
{
    qDebug() << __func__ << "START";

    m_xmlReader.ReadXmlFile("/storage/emulated/0/Download/modelServer.xml");
    m_xmlReader.ParserXml(&m_model);
    qDebug() << __func__ << "END";
}

void Controller::receMsg(const QString &msg)
{
    qDebug() << __func__;
    qDebug() << "____________________________________";
}
