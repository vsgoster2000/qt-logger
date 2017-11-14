#include <logger/moonlogger.h>
#include <logger/loggermanager.h>

namespace moon{
QMutex MoonLogger::sMutex;
MoonLogger *MoonLogger::sMoonLogger = NULL;

void MoonLogger::init(const LoggingPolicyPtr &policy){
    LoggerManager::getInstance().registerCategory(MoonLogger::categoryName(), policy);
}

}  // moon
