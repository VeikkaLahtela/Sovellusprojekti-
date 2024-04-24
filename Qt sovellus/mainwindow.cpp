#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString site_url = "http://localhost:3000/car";
    QNetworkRequest request((site_url));

    getManager = new QNetworkAccessManager(this);

    connect(getManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getBookSlot(QNetworkReply*)));

    reply = getManager->get(request);
}

void MainWindow::getBookSlot(QNetworkReply *reply)
{
    response_data = reply->readAll();
    qDebug() << "DATA: " + response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString cars;
    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        cars += QString::number(json_obj["id_car"].toInt()) + ", " + json_obj["branch"].toString() + ", " + json_obj["model"].toString() + "\r";
    }

    ui->textBooks->setText(cars);

    reply->deleteLater();
    getManager->deleteLater();
}

void MainWindow::on_btnpost_clicked()
{
    QString branch = ui->lineEditbranch->text();
    QString model = ui->lineEditmodel->text();

    QJsonObject jsonObj;
    jsonObj.insert("branch", branch);
    jsonObj.insert("model", model);

    QString site_url="http://localhost:3000/car";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");


    postManager = new QNetworkAccessManager(this);
    connect(postManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(addBookSlot(QNetworkReply*)));

    reply = postManager->post(request, QJsonDocument(jsonObj).toJson());
}

void MainWindow::addBookSlot (QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    reply->deleteLater();
    postManager->deleteLater();
}



void MainWindow::on_btnupdate_clicked()
{


        QString id = ui->lineEditId->text();
        QString branch = ui->lineEditbranch->text();
        QString model = ui->lineEditmodel->text();

        QJsonObject jsonObj;
        jsonObj.insert("branch", branch);
        jsonObj.insert("model", model);


        QString site_url = "http://localhost:3000/car/" + id;
        QNetworkRequest request((site_url));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");


        putManager = new QNetworkAccessManager(this);
        connect(putManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(updateBookSlot(QNetworkReply*)));

        reply = putManager->put(request, QJsonDocument(jsonObj).toJson());


}
void MainWindow::updateBookSlot (QNetworkReply *reply)
{
        response_data=reply->readAll();
        qDebug()<<response_data;
        reply->deleteLater();
        putManager->deleteLater();
}

void MainWindow::on_btndelete_clicked()
{


        QString id = ui->lineEditId->text();

        QString site_url = "http://localhost:3000/car/" + id;
        QNetworkRequest request((site_url));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");


        deleteManager = new QNetworkAccessManager(this);
        connect(deleteManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(deleteBookSlot(QNetworkReply*)));

        reply = deleteManager->deleteResource(request);


}

void MainWindow::deleteBookSlot (QNetworkReply *reply)
{
        response_data=reply->readAll();
        qDebug()<<response_data;
        reply->deleteLater();
        deleteManager->deleteLater();
}
