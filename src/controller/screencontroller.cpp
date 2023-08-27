#include "screencontroller.h"
#include "Views.h"

ScreenController* ScreenController::m_instance = nullptr;

ScreenController::ScreenController(QObject *parent)
    : QObject(parent)
    , m_initialized(false)
    , m_engine(nullptr)
{
   // LOG_INFO << "START";

 //   LOG_INFO << "END";
}

ScreenController::~ScreenController()
{
    qDebug()<< __func__ << "START";
    m_engine = nullptr;
    qDebug()<< __func__ << "END";
}

ScreenController *ScreenController::getInstance()
{
    if(m_instance == nullptr)
    {
        m_instance = new ScreenController();
    }

    return m_instance;
}

void ScreenController::initialize(QQmlContext *context)
{
    qDebug()<< __func__ << "START";
    qDebug()<< m_initialized;
    if(!m_initialized)
    {
        m_initialized = true;
     //   context->setContextProperty("SCREEN_CTRL", this);
   //     context->setContextProperty("SCREEN_MODEL", &m_model);
    }
    qDebug()<< __func__ << "END";
}

void ScreenController::initializeScreen(QQmlApplicationEngine *engine)
{
    qDebug()<< __func__ << "START";
    if(m_engine == nullptr)
    {
        m_engine = engine;

        // load main qml
    //    m_engine->load(QUrl(QStringLiteral(MAIN_QML)));

        //show home screen
   //     pushScreen("qrc:/qml/screens/HomeScreen.qml");
    }
    qDebug()<< __func__ << "END";
}
