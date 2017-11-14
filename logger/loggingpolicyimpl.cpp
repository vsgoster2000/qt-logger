#include <logger/loggingpolicyimpl.h>
#include <logger/loggingconfiguration.h>
#include <logger/loggingfile.h>

#include <QDebug>
#include <QMutexLocker>
#include <QThreadPool>

namespace moon{
class LoggingTask : public QRunnable
{
public:
    LoggingTask(const LoggingPolicyImpl *loggingPolicy, const QString &text) : mLoggingPolicy(loggingPolicy), mText(text){

    }

    void run() Q_DECL_OVERRIDE{
        Q_ASSERT(NULL != mLoggingPolicy);
        mLoggingPolicy->append(mText);
    }
private:
    QString mText;
    const LoggingPolicyImpl *mLoggingPolicy;
};

LoggingPolicyImpl::LoggingPolicyImpl(const LoggingFilePtr& loggingFile, LoggingLevel level)
    : LoggingPolicy(level), mLoggingFile(loggingFile), mThreadPool(std::shared_ptr<QThreadPool>(new QThreadPool())){
    mThreadPool->setMaxThreadCount(1);
    mThreadPool->setExpiryTimeout(300 * 1000);
}

LoggingPolicyImpl::~LoggingPolicyImpl(){
    Q_ASSERT(NULL != mThreadPool);
    Q_ASSERT(mThreadPool->maxThreadCount() == 1);
}

void LoggingPolicyImpl::logging(const QString &records, LoggingLevel level) const{
    if (!shouldLogging(level)){
        return ;
    }

    Q_ASSERT(NULL != mThreadPool);
    mThreadPool->start(new LoggingTask(this, records));
}

void LoggingPolicyImpl::append(const QString &records) const{
    mLoggingFile->logging(records);
}


}  // moon
