#include <logger/loggingpolicy.h>


namespace moon{

LoggingPolicy::LoggingPolicy(LoggingLevel level){
    mLevel = level;
}

LoggingPolicy::~LoggingPolicy(){}

}  // ~moon
