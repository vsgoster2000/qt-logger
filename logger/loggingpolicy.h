#ifndef PLATFORM_LOGGER_LOGGINGPOLICY_H
#define PLATFORM_LOGGER_LOGGINGPOLICY_H

#include <logger/loggingdefine.h>

#include <memory>
#include <qglobal.h>

QT_BEGIN_NAMESPACE
class QString;
QT_END_NAMESPACE

namespace moon {

/**
 * @brief The LoggingPolicy class defines a interface for logging messages to destinations,
 * user should subclass this class and at least implement the @logging(const QString& msg, LoggingLevel level) method.
 * User could set the logging level to filter messages.
 */
class LoggingPolicy{
public:
    explicit LoggingPolicy(LoggingLevel level = LoggingLevel::LEVEL_INFO);
    virtual ~LoggingPolicy();

    virtual void logging(const QString& msg, LoggingLevel level) const = 0;

    void setLoggingLevel(LoggingLevel level) { mLevel = level;}

    LoggingLevel loggingLevel() const {return mLevel;}

    // Returns true indicate that the message of this level should be logging.
    bool shouldLogging(LoggingLevel level) const {return level >= mLevel;}
private:
    LoggingLevel mLevel;

};  // ~LoggingPolicy


typedef std::shared_ptr<LoggingPolicy> LoggingPolicyPtr;
}  // ~moon

#endif // PLATFORM_LOGGER_LOGGINGPOLICY_H
