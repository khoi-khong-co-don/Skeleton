#include "QOutlog.h"

QOutlog::QOutlog()
{
    mStream.setString(&mLogString);
}

QOutlog::~QOutlog()
{
    if(mLogString.endsWith(QLatin1Char(' '))) {
        mLogString.chop(1);
    }
#ifdef USE_3RD_DEBUG
    qDebug() << mLogString;
#else
    qDebug() << mLogString;
#endif
}

QOutlog &QOutlog::begin(LOG_LEVEL level)
{
    m_level = level;
#ifdef USE_3RD_DEBUG
    // To request write log to the 3rd party of debuger (such as dlt)
#else
    mStream << "[#" << QThread::currentThreadId() << ']';
#endif
    return *this;
}

LogVerbose::LogVerbose()
{
#ifdef USE_3RD_DEBUG
    // To request write log to the 3rd party of debuger (such as dlt)
#else
    qInstallMessageHandler(this->verboseMessageHandler);
#endif
}

LogVerbose::~LogVerbose()
{

}

void LogVerbose::verboseMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &_msg)
{
    if(QtDebugMsg != type){
        DBG_ERROR << _msg;
    }
    else{
        if(0 == strcmp(context.category, "qml")){
            DBG_QT_MSG << _msg;
        }
    }
}

LogVerbose g_verbose;
