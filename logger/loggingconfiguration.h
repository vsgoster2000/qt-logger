#ifndef PLATFORM_LOGGER_LOGGINGCONFIGURATION_H
#define PLATFORM_LOGGER_LOGGINGCONFIGURATION_H

#include <QDir>
#include <QString>

namespace moon{
static const quint64 DEFAULT_MAX_LOG_FILE_BYTES = 10 * 1024 * 1024;
static const quint16 DEFAULT_MAX_LOG_FILE_COUNTS = 30;
static const QString DEFAULT_PREFIX_NAME("log");
static const QString DEFAULT_LOG_DIR("log");

class LoggingConfiguration{
public:
    enum OutputMode{DEBUG, RELEASE, TEST};
    static LoggingConfiguration create(){
        return create(QDir(DEFAULT_LOG_DIR), DEFAULT_PREFIX_NAME, DEFAULT_MAX_LOG_FILE_BYTES, DEFAULT_MAX_LOG_FILE_COUNTS);
    }

    static LoggingConfiguration create(const QDir& logDir){
        return create(logDir, DEFAULT_PREFIX_NAME, DEFAULT_MAX_LOG_FILE_BYTES, DEFAULT_MAX_LOG_FILE_COUNTS);
    }

    static LoggingConfiguration create(const QDir& logDir, const QString& filePrefixName){
        return create(logDir, filePrefixName, DEFAULT_MAX_LOG_FILE_BYTES, DEFAULT_MAX_LOG_FILE_COUNTS);
    }

    static LoggingConfiguration create(const QDir& logDir, const QString& filePrefixName, quint64 maxLogFilesBytes, quint16 maxLogFileCounts){
        LoggingConfiguration conf;
        conf.setLogDir(logDir);
        conf.setFilePrefixName(filePrefixName);
        conf.setMaxLogFileCounts(maxLogFileCounts);
        conf.setMaxLogFileBytes(maxLogFilesBytes);

        return conf;
    }

    quint16 maxLogFileCounts() const {return mMaxLogFileCounts;}
    quint64 maxLogFileBytes() const {return mMaxLogFileBytes;}
    QString filePrefixName() const {return mFilePrefixName;}
    QDir logDir() const {return mLogDir;}

    LoggingConfiguration& setMaxLogFileCounts(int maxLogFileCounts){
        mMaxLogFileCounts = maxLogFileCounts;
        return *this;
    }

    LoggingConfiguration& setMaxLogFileBytes(qint64 maxLogFileBytes){
        mMaxLogFileBytes = maxLogFileBytes;
        return *this;
    }

    LoggingConfiguration& setFilePrefixName(const QString& filePrefixName){
        mFilePrefixName = filePrefixName;
        return *this;
    }

    LoggingConfiguration& setLogDir(const QDir& logDir){
        mLogDir = logDir;
        return *this;
    }

private:
    // maximum file count for logging, exceed this limsitation will delete some old log files,
    // until this limitation satisfied.
    quint16 mMaxLogFileCounts;

    // maximum bytes for a log file, if the current log file exceed the limitation,
    // system will archive this log file, and create a new log file for logging.
    quint64 mMaxLogFileBytes;

    QString mFilePrefixName;
    QDir mLogDir;
};



}  // ~moon

#endif // PLATFORM_LOGGER_LOGGINGCONFIGURATION_H
