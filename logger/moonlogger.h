#ifndef PLATFORM_LOGGER_MOONLOGGER_H
#define PLATFORM_LOGGER_MOONLOGGER_H

#include <logger/loggermanager.h>

#include <QMutex>

namespace moon{

class MoonLogger
{
protected:
    MoonLogger(){
        mLevel = LoggingLevel::LEVEL_DEBUG;
    }
public:
    static MoonLogger& getInstance(){
        if (NULL == sMoonLogger){
            sMutex.lock();
            if (NULL == sMoonLogger){
                sMoonLogger = new MoonLogger();
            }
            sMutex.unlock();
        }
        return *sMoonLogger;
    }

    void init(const LoggingPolicyPtr &policy);

    void setLevel(LoggingLevel loggingLevel){ mLevel = loggingLevel;}

    LoggingLevel getLevel() const {return mLevel;}
    virtual const char* categoryName() const {return "moon";}

public:
    static QMutex sMutex;
    static MoonLogger* sMoonLogger;
    LoggingLevel mLevel;
};

}  // moon


#define logger_debug(...) \
    for (bool enabled = moon::MoonLogger::getInstance().getLevel() <= moon::LoggingLevel::LEVEL_DEBUG; enabled; enabled = false) \
        QMessageLogger(strrchr((const char*)(QT_MESSAGELOG_FILE), '\\') ? (strrchr((const char*)(QT_MESSAGELOG_FILE), '\\') + 1) : QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC, moon::MoonLogger::getInstance().categoryName()).debug(__VA_ARGS__)\

#define logger_info(...) \
    for (bool enabled = moon::MoonLogger::getInstance().getLevel() <= moon::LoggingLevel::LEVEL_INFO; enabled; enabled = false) \
        QMessageLogger(strrchr((const char*)(QT_MESSAGELOG_FILE), '\\') ? (strrchr((const char*)(QT_MESSAGELOG_FILE), '\\') + 1) : QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC, moon::MoonLogger::getInstance().categoryName()).info(__VA_ARGS__)\

#define logger_warn(...) \
    for (bool enabled = moon::MoonLogger::getInstance().getLevel() <= moon::LoggingLevel::LEVEL_WARN; enabled; enabled = false) \
        QMessageLogger(strrchr((const char*)(QT_MESSAGELOG_FILE), '\\') ? (strrchr((const char*)(QT_MESSAGELOG_FILE), '\\') + 1) : QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC, moon::MoonLogger::getInstance().categoryName()).warning(__VA_ARGS__)\

#define logger_error(...) \
    for (bool enabled = moon::MoonLogger::getInstance().getLevel() <= moon::LoggingLevel::LEVEL_ERROR; enabled; enabled = false) \
        QMessageLogger(strrchr((const char*)(QT_MESSAGELOG_FILE), '\\') ? (strrchr((const char*)(QT_MESSAGELOG_FILE), '\\') + 1) : QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC, moon::MoonLogger::getInstance().categoryName()).critical(__VA_ARGS__)\



#endif // PLATFORM_LOGGER_MOONLOGGER_H
