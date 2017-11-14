#ifndef PLATFORM_LOGGER_LOGGINGPOLICYIMPL_H
#define PLATFORM_LOGGER_LOGGINGPOLICYIMPL_H

#include <logger/loggingpolicy.h>

QT_BEGIN_NAMESPACE
class QString;
class QThreadPool;
QT_END_NAMESPACE

namespace moon{

class LoggingPolicyImpl : public LoggingPolicy
{
     Q_DISABLE_COPY(LoggingPolicyImpl)
public:
    explicit LoggingPolicyImpl(const LoggingFilePtr& loggingFile, LoggingLevel level = LoggingLevel::LEVEL_INFO);
    virtual ~LoggingPolicyImpl();

    virtual void logging(const QString& msg, LoggingLevel level) const;
private:
    friend class LoggingTask;
    void append(const QString& records) const;
private:
    const LoggingFilePtr mLoggingFile;
    const std::shared_ptr<QThreadPool> mThreadPool;
};


}  // moon
#endif // PLATFORM_LOGGER_LOGGINGPOLICYIMPL_H
