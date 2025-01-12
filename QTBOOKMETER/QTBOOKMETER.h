#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QTBOOKMETER.h"

#include <qnetworkaccessmanager.h>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QNetworkReply>
#include <qboxlayout.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <qfile.h>
#include <qfileinfo.h>
#include <qmessagebox.h>


class QTBOOKMETER : public QMainWindow
{
    Q_OBJECT

public:
    QTBOOKMETER(QWidget *parent = nullptr);
    ~QTBOOKMETER();

    void API_Request(QString searchQuery);
    void replyFinished(QNetworkReply* reply);
    void addBookToList(QString title, QString author, int pageCount, QString coverUrl, int userId, QString API_BookId);
    void getUserId(int& currentUserId);
    void checkDatabase(int userId, QString API_BookId, bool& read, bool& reading, bool& wantRead);

    int resultCount;

    int currentUserId;
   
    bool update;

private:
    Ui::QTBOOKMETERClass ui;

private slots:
    void on_searchButton_clicked();
};
