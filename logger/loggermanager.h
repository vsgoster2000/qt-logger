#ifndef PLATFORM_LOGGER_LOGGERMANAGER_H
#define PLATFORM_LOGGER_LOGGERMANAGER_H

#include <logger/loggingdefine.h>

#include <memory>

#include <QLoggingCategory>
#include <QMap>
#include <QMessageLogContext>
#include <QMutex>
#include <QString>

namespace moon{
class LoggerManager
{
public:
    static LoggerManager& getInstance(){
        if (NULL == sLoggerManager){
            sMutex.lock();
            if (NULL == sLoggerManager){
                sLoggerManager = new LoggerManager();
            }
            sMutex.unlock();
        }
        return *sLoggerManager;
    }

    void registerCategory(const char *categoryName, const LoggingPolicyPtr &policy){
        registerCategory(QString(categoryName), policy);
    }

    void registerCategory(const QString& category, const LoggingPolicyPtr &policy);

    QMap<QString, LoggingPolicyPtr>& categories() {return mCategories;}
private:
    LoggerManager();
    static void qtMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);
private:
    static QMutex sMutex;
    static LoggerManager *sLoggerManager;
    QMap<QString, LoggingPolicyPtr> mCategories;
};  // ~LoggerManager



}  // ~moon
#endif // PLATFORM_LOGGER_LOGGERMANAGER_H
