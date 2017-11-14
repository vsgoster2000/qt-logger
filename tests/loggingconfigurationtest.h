#ifndef LOGGINGCONFIGURATIONTEST_H
#define LOGGINGCONFIGURATIONTEST_H

#include <logger/loggingconfiguration.h>

#include <QDebug>
#include <QString>
#include <QtTest>

using namespace moon;

class LoggingConfigurationTest : public QObject
{
    Q_OBJECT
public:
    LoggingConfigurationTest(){}
private Q_SLOTS:
    void createTest1(){
        const LoggingConfiguration conf = LoggingConfiguration::create();
        QVERIFY(conf.logDir().absolutePath() == QDir(DEFAULT_LOG_DIR).absolutePath());
        QVERIFY(conf.filePrefixName() == DEFAULT_PREFIX_NAME);
        QVERIFY(conf.maxLogFileBytes() == DEFAULT_MAX_LOG_FILE_BYTES);
        QVERIFY(conf.maxLogFileCounts() == DEFAULT_MAX_LOG_FILE_COUNTS);
    }

    void createTest2(){
        const QDir dir("test");
        const LoggingConfiguration conf = LoggingConfiguration::create(dir);
        QVERIFY(conf.logDir().absolutePath() == dir.absolutePath());
        QVERIFY(conf.filePrefixName() == DEFAULT_PREFIX_NAME);
        QVERIFY(conf.maxLogFileBytes() == DEFAULT_MAX_LOG_FILE_BYTES);
        QVERIFY(conf.maxLogFileCounts() == DEFAULT_MAX_LOG_FILE_COUNTS);
    }

    void createTest3(){
        const QDir dir("test");
        const QString prefixName = "vsgoster";
        const LoggingConfiguration conf = LoggingConfiguration::create(dir, prefixName);
        QVERIFY(conf.logDir().absolutePath() == dir.absolutePath());
        QVERIFY(conf.filePrefixName() == prefixName);
        QVERIFY(conf.maxLogFileBytes() == DEFAULT_MAX_LOG_FILE_BYTES);
        QVERIFY(conf.maxLogFileCounts() == DEFAULT_MAX_LOG_FILE_COUNTS);
    }

    void createTest4(){
        const QDir dir("test");
        const QString prefixName = "vsgoster";
        const qint64 bytes = 1024;
        const int count = 5;

        const LoggingConfiguration conf = LoggingConfiguration::create(dir, prefixName, bytes, count);
        QVERIFY(conf.logDir().absolutePath() == dir.absolutePath());
        QVERIFY(conf.filePrefixName() == prefixName);
        QVERIFY(conf.maxLogFileBytes() == bytes);
        QVERIFY(conf.maxLogFileCounts() == count);
    }
};

#endif // LOGGINGCONFIGURATIONTEST_H
