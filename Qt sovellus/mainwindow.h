#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void getBookSlot (QNetworkReply *reply);
    void addBookSlot (QNetworkReply *reply);
    void updateBookSlot (QNetworkReply *reply);
    void deleteBookSlot (QNetworkReply *reply);

    void on_pushButton_clicked();

    void on_btnpost_clicked();

    void on_btnupdate_clicked();

    void on_btndelete_clicked();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *getManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QNetworkAccessManager *postManager;
    QNetworkAccessManager *putManager;
    QNetworkAccessManager *deleteManager;

};
#endif
