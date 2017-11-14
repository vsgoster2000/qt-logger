#include <logger/loggingfile.h>
#include <logger/loggingconfiguration.h>

#include <QDateTime>
#include <QDebug>
#include <QTextStream>

namespace moon{

//static const qint64 DEFAULT_MAX_LOG_FILE_BYTES = 10 * 1024 * 1024;
//static const int DEFAULT_MAX_LOG_FILE_COUNTS = 30;
//static const QString DEFAULT_PREFIX_NAME("log");
static const QString DEFAULT_LOG_POSTFIX = ".log";
static const QString DEFAULT_BACKUP_POSTFIX = ".bak";

LoggingFilePtr LoggingFile::create(const LoggingConfiguration& conf) {
    if ( (!conf.logDir().exists()) || (conf.filePrefixName().isEmpty())){
        qCritical() << "Create LoggingFile failed, invalid argument.";
        return NULL;
    }

    LoggingFile* loggingFile = new LoggingFile(conf.logDir(), conf.filePrefixName(), conf.maxLogFileBytes(), conf.maxLogFileCounts());
    if (!loggingFile->init()){
        delete loggingFile;
        loggingFile = NULL;
        return NULL;
    }

    return LoggingFilePtr(loggingFile);
}

LoggingFile::LoggingFile(const QDir& dir, const QString& prefix, qint64 maxLogFilesBytes, long maxLogFileCounts)
    : mLogDir(dir), mFilePrefixName(prefix),
      mMaxLogFilesBytes(maxLogFilesBytes), mMaxLogFileCounts(maxLogFileCounts)
{
    mLogFile = NULL;
}

LoggingFile::~LoggingFile(){
    if (NULL != mLogFile){
        if (mLogFile->isOpen()){
            mLogFile->close();
            mLogFile = NULL;
        }
    }
}

void LoggingFile::logging(const QString &text){
    if (NULL == mLogFile){
        qWarning() << "mLogFile is NULL.";
        return ;
    }

    if (!rollLogFile()){
        return ;
    }
    QTextStream textStream(mLogFile);
    textStream << text << endl;
    mLogFile->flush();
}

bool LoggingFile::init() {
    if (!initLogFile()){
        return false;
    }

    return true;
}

bool LoggingFile::initLogFile(){
    Q_ASSERT(NULL == mLogFile);

    QString logFilename;
    QStringList lists = mLogDir.entryList(QStringList("*" + DEFAULT_LOG_POSTFIX), QDir::Files, QDir::Time);
    if (lists.size() == 0){
        return generateNewLogFile();
    }else if (lists.size() == 1){
        logFilename = lists.at(0);
    }else{
        int size = lists.size();
        for (int i = 0; i < size - 1; ++i){
            backupLogFile(mLogDir.absoluteFilePath(lists.at(i)));
        }
        logFilename = lists.at(size - 1);
    }

    QString dateString = QDateTime::currentDateTime().toString("yyyyMMdd");
    if (logFilename.contains(dateString)){
        return generateLogFile(mLogDir.absoluteFilePath(logFilename));
    }

    backupLogFile(mLogDir.absoluteFilePath(logFilename));
    return generateNewLogFile();
}

bool LoggingFile::generateLogFile(const QString& absolutePath) {
    if (NULL != mLogFile){
        if (mLogFile->isOpen()){
            mLogFile->close();
        }
        delete mLogFile;
        mLogFile = NULL;
    }

    mLogFile = new QFile(absolutePath);
    if (!mLogFile->open(QIODevice::WriteOnly | QIODevice::Append)){
        qDebug() << "Open file:" << absolutePath << " failed.";
        return false;
    }
    return true;
}

bool LoggingFile::generateNewLogFile() {
    QString filename = mFilePrefixName + "-" + QDateTime::currentDateTime().toString("yyyyMMdd-hhmmss-zzz") + DEFAULT_LOG_POSTFIX;
    qDebug() << "Create new log file:" << filename;
    return generateLogFile(mLogDir.absoluteFilePath(filename));
}

void LoggingFile::backupLogFile(const QString &absolutePath) {
    Q_ASSERT(QDir::isAbsolutePath(absolutePath));
    if (!QFile::rename(absolutePath, absolutePath + DEFAULT_BACKUP_POSTFIX)){
        qWarning() << "File backup failed, file:" << absolutePath.mid(absolutePath.lastIndexOf('/')+1);
        return ;
    }
    trimToFileCount();
}

void LoggingFile::trimToFileCount(){
    QStringList lists = mLogDir.entryList(QStringList("*" + DEFAULT_BACKUP_POSTFIX), QDir::Files, QDir::Time | QDir::Reversed);
    if (mMaxLogFileCounts >= lists.size()){
        return ;
    }

    int removeNo = lists.size() - mMaxLogFileCounts;
    for (int i = 0; i < removeNo; ++i){
        qDebug() << "Remove log file:" << lists.at(i);
        mLogDir.remove(lists.at(i));
    }
}

bool LoggingFile::rollLogFile() {
    Q_ASSERT(NULL != mLogFile);

    QString dateString = QDateTime::currentDateTime().toString("yyyyMMdd");
    if (!mLogFile->fileName().contains(dateString)){
        qDebug() << "Log file is out of date, current date:" << dateString << ", current log file:" << mLogFile->fileName();
        Q_ASSERT(mLogFile->isOpen());

        mLogFile->close();  // close log file before backup it.
        // If current log file is out of date, backup it and create a new one.
        backupLogFile(mLogDir.absoluteFilePath(mLogFile->fileName()));
        return generateNewLogFile();
    }

    QFileInfo fileinfo(mLogDir, mLogFile->fileName());
    if (static_cast<quint64>(fileinfo.size()) > mMaxLogFilesBytes){
        qDebug() << "Log file bytes:" << fileinfo.size() << " exceed limitation:" << mMaxLogFilesBytes;
        Q_ASSERT(mLogFile->isOpen());

        mLogFile->close();  // close log file before backup it.
        // If current log file's bytes exceed limitation, backup it and create a new one.
        backupLogFile(mLogDir.absoluteFilePath(mLogFile->fileName()));
        return generateNewLogFile();
    }

    return true;
}




}  // ~moon
