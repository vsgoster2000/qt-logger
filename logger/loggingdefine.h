#ifndef PLATFORM_LOGGER_LOGGINGDEFILE_H
#define PLATFORM_LOGGER_LOGGINGDEFILE_H

#include <memory>

namespace moon{
enum LoggingLevel{LEVEL_DEBUG, LEVEL_INFO, LEVEL_WARN, LEVEL_ERROR, LEVEL_FATAL, LEVEL_OFF};

class LoggingConfiguration;
class LoggingFile;
class LoggingPolicy;
typedef std::shared_ptr<LoggingFile> LoggingFilePtr;
typedef std::shared_ptr<LoggingPolicy> LoggingPolicyPtr;
}  // ~moon
#endif // PLATFORM_LOGGER_LOGGINGDEFILE_H
