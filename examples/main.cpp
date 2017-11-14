#include "loggerexampledialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoggerExampleDialog w;
    w.show();

    return a.exec();
}
