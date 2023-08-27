#include "appengine.h"
#include <QDebug>
AppEngine* AppEngine::m_instance = nullptr;

AppEngine::AppEngine(QObject *parent)
    : QObject(parent)
    , m_initialized(false)
    , m_app(nullptr)
{
    qDebug() << __func__ << "START";
    QQuickViewer::registerStates(STATE_ALL, ALEN(STATE_ALL));
    qDebug() << __func__<< "END";
}

AppEngine::~AppEngine()
{
    qDebug() << __func__ << "START";
    m_app = nullptr;
    qDebug() << __func__<< "END";
}

AppEngine *AppEngine::getInstance()
{
    qDebug() << __func__ << "START";
    if(m_instance == nullptr)
    {
        m_instance = new AppEngine();
    }
    qDebug() << __func__ << "END";
    return m_instance;
}

void AppEngine::initialize(QApplication *app)
{
    qDebug() << __func__ << "START";
    if(!m_initialized)
    {
        m_initialized = true;
        m_app = app;
        // init home application
        registerQmlObjects();
        createControllers();
        initControllers();
        initScreens();

    }
    qDebug() << __func__ << "END";
}

EditServerModel *AppEngine::editModel()
{
    qDebug() <<__func__ << QString::number(reinterpret_cast<quintptr>(EditServerController::getInstance()->getInstanceModel()), 16);
    return EditServerController::getInstance()->getInstanceModel();
}

void AppEngine::registerQmlObjects()
{
    qDebug() << __func__ << "START";

    qmlRegisterType<E>("HMIEVENTS", 1, 0, "EVT");
    qDebug() << __func__ << "END";
}

void AppEngine::createControllers()
{
    qDebug() << __func__ << "START";
    m_view = QQuickViewer::getInstance((uchar)VIEWER_INDEX::VIEWER_1ST);
    QQuickViewer::getInstance((uchar)VIEWER_INDEX::VIEWER_1ST)->initialized();
    QQuickViewer::getInstance((uchar)VIEWER_INDEX::VIEWER_1ST)->completed();


    Controller::getInstance();
    EditServerController::getInstance();

    qDebug() << __func__ << "END";
}

void AppEngine::initControllers()
{
    qDebug() << __func__ << "START";
    Controller::getInstance()->initialize(m_view);
    EditServerController::getInstance()->initialize(m_view);
    qDebug() << __func__ << "END";
}

void AppEngine::initScreens()
{
    qDebug() << __func__ << "START";


    QQuickViewer::getInstance((uchar)VIEWER_INDEX::VIEWER_1ST)->sendEvent(E::EVT_BLK_TO_SCREEN_B, "4");
    QQuickViewer::getInstance((uchar)VIEWER_INDEX::VIEWER_1ST)->show();
    qDebug() <<QString::number(reinterpret_cast<quintptr>( QQuickViewer::getInstance((uchar)VIEWER_INDEX::VIEWER_1ST)), 16);


    qDebug() << __func__ << "END";
}


