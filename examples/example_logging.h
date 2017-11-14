#ifndef EXAMPLE_LOGGINGFILE_H
#define EXAMPLE_LOGGINGFILE_H

#include <logger/loggingfile.h>
#include <logger/LoggingConfiguration.h>
#include <logger/loggingpolicyimpl.h>
#include <logger/moonlogger.h>

#include <QDebug>
#include <QString>

using namespace moon;

class LoggingExample{
public:
    LoggingExample(){

        QDir logDir("log");
        if (!logDir.mkpath(logDir.absolutePath())){
            qDebug() << "Should not create logging directory.";
            return ;
        }

        mLoggingFile = LoggingFile::create(LoggingConfiguration::create(logDir, "test", 1024, 3));
        if (NULL == mLoggingFile){
            qDebug() << "Could not create LoggingFile.";
            return ;
        }

        mLoggingPolicy = LoggingPolicyPtr(new LoggingPolicyImpl(mLoggingFile));
        //MoonLogger::getInstance().init(mLoggingPolicy);
    }

    void loggingToFile(int recordNum){
        if (NULL == mLoggingFile){
            return ;
        }
        QString logTextPrefix = "loggingToFile-012345678901234567890123456789012345678901234567890123456789---";
        for (int i = 1; i <= recordNum; ++i){
            mLoggingFile->logging(logTextPrefix + QString::number(i));
        }
    }

    void loggingToPolicy(int recordNum){
        if (NULL == mLoggingPolicy){
            return ;
        }

        QString logTextPrefix = "loggingToPolicy-012345678901234567890123456789012345678901234567890123456789---";
        //        for (int i = 1; i <= recordNum/8; ++i){
        //            mLoggingPolicy->logging(logTextPrefix + QString::number(i), LoggingLevel::LEVEL_DEBUG);
        //            mLoggingPolicy->logging(logTextPrefix + QString::number(i), LoggingLevel::LEVEL_INFO);
        //            mLoggingPolicy->logging(logTextPrefix + QString::number(i), LoggingLevel::LEVEL_WARN);
        //            mLoggingPolicy->logging(logTextPrefix + QString::number(i), LoggingLevel::LEVEL_ERROR);
        //        }

        mLoggingPolicy->logging(logTextPrefix + QString::number(recordNum), LoggingLevel::LEVEL_DEBUG);
        mLoggingPolicy->logging(logTextPrefix + QString::number(recordNum), LoggingLevel::LEVEL_INFO);
        mLoggingPolicy->logging(logTextPrefix + QString::number(recordNum), LoggingLevel::LEVEL_WARN);
        mLoggingPolicy->logging(logTextPrefix + QString::number(recordNum), LoggingLevel::LEVEL_ERROR);
    }

    void loggingToMoonLogger(){
        LoggerManager::getInstance();
        logger_debug("logger_debug::loggingToMoonLogger-01234567890-Test!");
        logger_info("logger_info::loggingToMoonLogger-01234567890-Test!");
        logger_warn("logger_warn::loggingToMoonLogger-01234567890-Test!");
        logger_error("logger_error::loggingToMoonLogger-01234567890-Test!");

        qDebug() << "loggingToMoonLogger-qDebug";
        qInfo() << "loggingToMoonLogger-qInfo";
        qWarning() << "loggingToMoonLogger-qWarning";
        qCritical() << "loggingToMoonLogger-qCritical";
    }

private:
    LoggingFilePtr mLoggingFile;
    LoggingPolicyPtr mLoggingPolicy;
};

#endif // EXAMPLE_LOGGINGFILE_H
