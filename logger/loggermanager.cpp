#include <logger/loggermanager.h>
#include <logger/loggingpolicy.h>
#include <logger/moonlogger.h>

#include <QDateTime>
#include <QString>
#include <QMutexLocker>

namespace moon{
static QString getMsgTypeString(QtMsgType type){
    switch (type) {
    case QtDebugMsg:
        return "DEBUG";
    case QtInfoMsg:
        return "INFO ";
    case QtWarningMsg:
        return "WARN ";
    case QtCriticalMsg:
        return "ERROR";
    case QtFatalMsg:
        return "FATAL";
    default:
        return "UNKNO";
    }
}

static LoggingLevel getLoggingLevel(QtMsgType type){
    switch (type) {
    case QtDebugMsg:
        return LoggingLevel::LEVEL_DEBUG;
    case QtInfoMsg:
        return LoggingLevel::LEVEL_INFO;
    case QtWarningMsg:
        return LoggingLevel::LEVEL_WARN;
    case QtCriticalMsg:
        return LoggingLevel::LEVEL_ERROR;
    case QtFatalMsg:
        return LoggingLevel::LEVEL_FATAL;
    default:
        return LoggingLevel::LEVEL_DEBUG;
    }
}

static void loggingToConsole(const QString& text){
    fprintf(stdout, "%s\n", text.toLocal8Bit().constData());
    fflush(stdout);
}

static const char* trimPath(const char *path){
    Q_ASSERT(NULL != path);
    const char *index = strrchr(path, '\\');
    if (NULL != index){
        return index+1;
    }
    return path;
}

QMutex LoggerManager::sMutex;
LoggerManager *LoggerManager::sLoggerManager = NULL;

LoggerManager::LoggerManager(){
    qInstallMessageHandler(qtMessageHandler);
}

void LoggerManager::qtMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg){
    QString dateTime = QDateTime::currentDateTime().toString("yyyyMMdd hh:mm:ss");
    QString loggingText;
    if (strcmp(context.category, MoonLogger::getInstance().categoryName()) == 0){
        loggingText = QString("%1 %2 %3 (%4:%5 %6)").arg(getMsgTypeString(type)).arg(dateTime).arg(msg).arg(context.file).arg(context.line).arg(context.category);

        LoggingPolicyPtr policy = LoggerManager::getInstance().mCategories.value(QString(context.category), NULL);
        if (NULL != policy){
            policy->logging(loggingText, getLoggingLevel(type));
            return ;
        }
    }else{
        loggingText = QString("%1 %2 %3 (%4:%5 %6)").arg(getMsgTypeString(type)).arg(dateTime).arg(msg).arg(trimPath(context.file)).arg(context.line).arg(context.category);
    }

    loggingToConsole(loggingText);
}

void LoggerManager::registerCategory(const QString &category, const LoggingPolicyPtr &policy){
    QMutexLocker guard(&sMutex);
    LoggerManager::getInstance().mCategories.insert(category, policy);
}





}  // ~moon
