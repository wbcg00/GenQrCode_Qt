#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QByteArray text;

    ui->widget->setQrCodeContent(text,QSize(200,200));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString info = ui->lineEdit->text();
    QByteArray text(info.toUtf8());

    ui->widget->setQrCodeIcon(QPixmap(":/medal.png"));
    ui->widget->setQrCodeCaseSensitive(true);
    ui->widget->setQrCodeContent(text,QSize(200,200));
}
