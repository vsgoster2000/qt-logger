#ifndef LOGGEREXAMPLEDIALOG_H
#define LOGGEREXAMPLEDIALOG_H

#include "example_logging.h"

#include <QDialog>

namespace Ui {
class LoggerExampleDialog;
}

class LoggerExampleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoggerExampleDialog(QWidget *parent = 0);
    ~LoggerExampleDialog();

private:
    Ui::LoggerExampleDialog *ui;
    LoggingExample mLoggingExample;
};

#endif // LOGGEREXAMPLEDIALOG_H
