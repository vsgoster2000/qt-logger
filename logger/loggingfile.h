#ifndef PLATFORM_LOGGER_LOGGINGFILE_H
#define PLATFORM_LOGGER_LOGGINGFILE_H

#include <logger/loggingdefine.h>

#include <memory>
#include <QDir>
#include <QFile>
#include <QString>

namespace moon{
class LoggingConfiguration;

class LoggingFile
{
    Q_DISABLE_COPY(LoggingFile)
public:
    /**
     * @brief Creates a @LoggingFile object and initialize it, if initialization success,
     * returns a pointer point to this the object, otherwise return NULL.
     * @param conf
     * @return Returns a LoggingFilePtr object if success, otherwise return NULL.
     */
    static LoggingFilePtr create(const LoggingConfiguration& conf);
    ~LoggingFile();

    void logging(const QString& text);

private:
    /**
     * @brief Constructor
     * @param dir A QDir object represent the directory in which all log file placed.
     * @param prefix A QString reference represent the prefix of the file name.
     * @param maxLogFilesBytes maximum bytes for a log file
     * @param maxLogFileCounts maximum file count for logging
     */
    LoggingFile(const QDir& dir, const QString& prefix, qint64 maxLogFilesBytes, long maxLogFileCounts);

    bool init();
    bool initLogFile();
    bool generateLogFile(const QString& absolutePath);
    bool generateNewLogFile();
    /**
     * @brief Backups log file specied by @absolutePath. Just simply add a postfix named '.bak' to the file.
     */
    void backupLogFile(const QString& absolutePath);
    /**
     * @brief Trims file count, if the number of log file exceeds the limitation,
     * system will remove some log file to satisfy this limitation, the oldest log file will be removed.
     */
    void trimToFileCount();

    /**
     * @brief Rolls log file, if log file is out of date or is larger than the @mMaxLogFilesBytes,
     * system will backup current log file and create a new log file for logging.
     * @return Returns true if rolling successful, false on failure.
     */
    bool rollLogFile();

private:
    // maximum file count for logging, exceed this limsitation will delete some old log files,
    // until this limitation satisfied.
    const quint16 mMaxLogFileCounts;

    // maximum bytes for a log file, if the current log file exceed the limitation,
    // system will archive this log file, and create a new log file for logging.
    const quint64 mMaxLogFilesBytes;

    const QString mFilePrefixName;
    QDir mLogDir;
    QFile* mLogFile;
};

}  // ~moon

#endif // PLATFORM_LOGGER_LOGGINGFILE_H
