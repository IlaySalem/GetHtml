#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished,this,[=](QNetworkReply* reply){
        if(reply->error() != QNetworkReply::NoError){
            qDebug() << reply->error() << reply->errorString();
            return;
        }
        QByteArray arr = reply->readAll();
        qDebug() << "arr: " << arr;
        ui->plainTextEdit->clear();
        ui->plainTextEdit->appendPlainText(QTextCodec::codecForMib(106)->toUnicode(arr));
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    manager->get(QNetworkRequest(QUrl(QString("%1").arg(ui->lineEdit->text()))));
}
