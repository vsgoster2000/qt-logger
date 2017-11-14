#include "loggingconfigurationtest.h"
#include <QCoreApplication>
#include <QDebug>
#include <QTest>

void addTest(QObject *testObject, bool failedToAbort = true)
{
    if (QTest::qExec(testObject) != 0){
        qCritical("Test [%s] failed!", testObject->metaObject()->className());
        if (failedToAbort){
            abort();
        }
    }
}

int main(int argc, char *argv[]){
    QCoreApplication(argc, argv);

    addTest(new LoggingConfigurationTest());
    return 0;
}


