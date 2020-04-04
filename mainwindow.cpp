#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished,this,[=](QNetworkReply* reply){
        QByteArray arr = reply->readAll();
        ui->plainTextEdit->clear();
        qDebug() << "arr: " << arr;
        ui->plainTextEdit->appendPlainText(QTextCodec::codecForMib(106)->toUnicode(arr));
        //ui->plainTextEdit->appendHtml(QTextCodec::codecForMib(106)->toUnicode(arr));
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
