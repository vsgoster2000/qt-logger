#include "loggerexampledialog.h"
#include "ui_loggerexampledialog.h"

LoggerExampleDialog::LoggerExampleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoggerExampleDialog)
{
    ui->setupUi(this);

    connect(ui->loggingToFile, &QPushButton::clicked, [this](){
        mLoggingExample.loggingToFile(ui->recordNums->text().toInt());
    });

    connect(ui->testPolicy, &QPushButton::clicked, [this](){
        mLoggingExample.loggingToPolicy(ui->recordNums->text().toInt());
    });

    connect(ui->testMoonLogger, &QPushButton::clicked, [this](){
        mLoggingExample.loggingToMoonLogger();
    });
}

LoggerExampleDialog::~LoggerExampleDialog()
{
    delete ui;
}
