#include "QTBOOKMETER.h"


QTBOOKMETER::QTBOOKMETER(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    getUserId(currentUserId);
    qDebug() << "CurrentUserId:" << currentUserId;
    QIcon searchIcon("C:\\Users\\xanda\\source\\repos\\QTBOOKMETER\\images\\magnifier.png");
    QIcon logoIcon("C:\\Users\\xanda\\source\\repos\\QTBOOKMETER\\images\\app_icon.png");

    ui.searchButton->setIcon(searchIcon);
    ui.iconLabel->setIcon(logoIcon);
    ui.iconLabel->setIconSize(QSize(90, 80));
    
}

QTBOOKMETER::~QTBOOKMETER()
{}



void QTBOOKMETER::addBookToList(QString title, QString author, int pageCount, QString coverUrl, int userId, QString API_BookId) {

    qDebug() << "List (" << title << "," << author << "," << pageCount << "," << coverUrl << "," << userId << "," << API_BookId << ")";
    QWidget* itemWidget = new QWidget(ui.listWidget);

    //Image
    QLabel* imageLabel = new QLabel(this);

    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, [=](QNetworkReply* reply) {
        QPixmap pixmap;

        if (pixmap.loadFromData(reply->readAll()))
        {
            imageLabel->setPixmap(pixmap);
            imageLabel->setMaximumSize(130, 190);
            imageLabel->setScaledContents(true);

        }
        else
        {

            qDebug() << "Failed to load image from data";
        }

        });

    QUrl imageUrl = coverUrl;
    manager->get(QNetworkRequest(imageUrl));
    //Image over

    QLabel* titleLabel = new QLabel(title);
    QLabel* authorLabel = new QLabel(author);
    QPushButton* readButton = new QPushButton("Read");
    QPushButton* readingButton = new QPushButton("Reading");
    QPushButton* wantButton = new QPushButton("Want to Read");


    // Layout setup for the widget
    QVBoxLayout* textLayout = new QVBoxLayout();
    
    textLayout->addWidget(titleLabel);
    textLayout->addWidget(authorLabel);
   
   
    QHBoxLayout* buttonLayout = new QHBoxLayout();

    buttonLayout->addWidget(readButton);
    buttonLayout->addWidget(readingButton);
    buttonLayout->addWidget(wantButton);
    buttonLayout->setSpacing(10);


    QHBoxLayout* mainLayout = new QHBoxLayout();
  
    if (resultCount >= 40)
    {
        ui.displayL->setText(QString::number(resultCount) + " Results Found!");
        ui.over4->setText(" (Limit reached! If you didn't find what you were looking for, please be more specific!)");
        qDebug() << "MESSAGE";
    }
    else {
        ui.displayL->setText(QString::number(resultCount) + " Results Found!");
    }

    bool read = false;
    bool reading = false;
    bool wantRead = false;

    const QString defaultStyle =
        "QPushButton {"
        "    border: 2px solid white;"
        "    border-radius: 15px;"
        "    background-color: #131121;"
        "    color: white;"
        "    padding: 5px 10px;"
        "}"
        "QPushButton:hover {"
        "    border: 2px solid white;"
        "    border-radius: 15px;"
        "    background-color: white;"
        "    color: #131121;"
        "    padding: 5px 10px;"
        "}";

    const QString activeStyle =
        "QPushButton {"
        "    border: 2px solid white;"
        "    border-radius: 15px;"
        "    background-color: white;"
        "    color: #131121;"
        "    padding: 5px 10px;"
        "}";

    checkDatabase(userId, API_BookId, read, reading, wantRead);

    connect(readButton, &QPushButton::clicked, this, [this, userId, API_BookId, readButton, readingButton, reading, wantButton, wantRead,defaultStyle,activeStyle]() {

        readButton->setStyleSheet(defaultStyle);
        readingButton->setStyleSheet(defaultStyle);
        wantButton->setStyleSheet(defaultStyle);

        QString status = "Read";
        QSqlDatabase db = QSqlDatabase::database();

        QSqlQuery query(db);

        //Check current status
        if (reading || wantRead)
        {

            QString currentStatus;
            if (reading)
            {
                currentStatus = "Reading";

                readingButton->setEnabled(true);

            }
            else if (wantRead)
            {
                currentStatus = "Want to Read";

                wantButton->setEnabled(true);
            }


            QSqlQuery query;
            query.prepare("UPDATE UserBooks "
                "SET Status = :newStatus "
                "WHERE UserId = :userId AND GoogleBooksId = :googleBooksId AND Status = :currentStatus");

            query.bindValue(":newStatus", "Read");
            query.bindValue(":userId", userId);
            query.bindValue(":googleBooksId", API_BookId);
            query.bindValue(":currentStatus", currentStatus);


            if (!query.exec()) {
                qDebug() << "Failed to update status:" << query.lastError().text();
            }
            else {
                qDebug() << "Status updated successfully.";
            }

        }
        else {

            query.prepare("INSERT INTO UserBooks (UserId, GoogleBooksId, Status) "
                "VALUES (:userId, :googleBooksId, :status)");
            query.bindValue(":userId", userId);
            query.bindValue(":googleBooksId", API_BookId);
            query.bindValue(":status", status);

            if (!query.exec()) {
                qDebug() << "Error inserting into UserBooks:" << query.lastError().text();

                QString errorMessage = query.lastError().text();
                QMessageBox::critical(nullptr, "Database Error!", errorMessage);
                return false;
            }
        }

        readButton->setStyleSheet(activeStyle);

        });

    //READING BUTTON
    connect(readingButton, &QPushButton::clicked, this, [this, userId, API_BookId, readingButton, readButton, read, wantButton, wantRead,defaultStyle,activeStyle]() {

        readButton->setStyleSheet(defaultStyle);
        readingButton->setStyleSheet(defaultStyle);
        wantButton->setStyleSheet(defaultStyle);

        QString status = "Reading";
        QSqlDatabase db = QSqlDatabase::database();

        QSqlQuery query(db);

        if (read || wantRead)
        {

            QString currentStatus;
            if (read)
            {
                currentStatus = "Read";

                readButton->setEnabled(true);

            }
            else if (wantRead)
            {
                currentStatus = "Want to Read";

                wantButton->setEnabled(true);
            }

      

            QSqlQuery query;
            query.prepare("UPDATE UserBooks "
                "SET Status = :newStatus "
                "WHERE UserId = :userId AND GoogleBooksId = :googleBooksId AND Status = :currentStatus");

            query.bindValue(":newStatus", "Reading");
            query.bindValue(":userId", userId);
            query.bindValue(":googleBooksId", API_BookId);
            query.bindValue(":currentStatus", currentStatus);


            if (!query.exec()) {
                qDebug() << "Failed to update status:" << query.lastError().text();
            }
            else {
                qDebug() << "Status updated successfully.";
            }

        }
        else {


            query.prepare("INSERT INTO UserBooks (UserId, GoogleBooksId, Status) "
                "VALUES (:userId, :googleBooksId, :status)");
            query.bindValue(":userId", userId);
            query.bindValue(":googleBooksId", API_BookId);
            query.bindValue(":status", status);

            if (!query.exec()) {
                qDebug() << "Error inserting into UserBooks:" << query.lastError().text();

                QString errorMessage = query.lastError().text();
                QMessageBox::critical(nullptr, "Database Error!", errorMessage);
                return false;
            }

        }

        readingButton->setStyleSheet(activeStyle);

        });

    //Want to Read BUTTON
    connect(wantButton, &QPushButton::clicked, this, [this, userId, API_BookId, wantButton, readButton, read, readingButton, reading,defaultStyle,activeStyle]() {

        readButton->setStyleSheet(defaultStyle);
        readingButton->setStyleSheet(defaultStyle);
        wantButton->setStyleSheet(defaultStyle);


        QString status = "Want to Read";
        QSqlDatabase db = QSqlDatabase::database();

        QSqlQuery query(db);

        if (read || reading)
        {

            QString currentStatus;
            if (read)
            {
                currentStatus = "Read";

                readButton->setEnabled(true);
             
            }
            else if (reading)
            {
                currentStatus = "Reading";

                readingButton->setEnabled(true);
            
            }

          

            QSqlQuery query;
            query.prepare("UPDATE UserBooks "
                "SET Status = :newStatus "
                "WHERE UserId = :userId AND GoogleBooksId = :googleBooksId AND Status = :currentStatus");

            query.bindValue(":newStatus", "Want to Read");
            query.bindValue(":userId", userId);
            query.bindValue(":googleBooksId", API_BookId);
            query.bindValue(":currentStatus", currentStatus);


            if (!query.exec()) {
                qDebug() << "Failed to update status:" << query.lastError().text();
            }
            else {
                qDebug() << "Status updated successfully.";
            }

        }
        else {
            query.prepare("INSERT INTO UserBooks (UserId, GoogleBooksId, Status) "
                "VALUES (:userId, :googleBooksId, :status)");
            query.bindValue(":userId", userId);
            query.bindValue(":googleBooksId", API_BookId);
            query.bindValue(":status", status);

            if (!query.exec()) {
                qDebug() << "Error inserting into UserBooks:" << query.lastError().text();

                QString errorMessage = query.lastError().text();
                QMessageBox::critical(nullptr, "Database Error!", errorMessage);
                return false;
            }

        }
        wantButton->setStyleSheet(activeStyle);

        });


    //checkDatabase(userId, API_BookId, read, reading, wantRead);

    //CSS
    itemWidget->setStyleSheet("background-color: #131121;padding: 10px; border-radius: 25px;");
    titleLabel->setStyleSheet("font-size: 30px;");
    authorLabel->setStyleSheet("font-size: 22px;");
    imageLabel->setStyleSheet("border: 10px solid #131121;border-radius: 25px;");

    if (!read) {
        readButton->setEnabled(true);
        readButton->setStyleSheet(defaultStyle);
    }
    else
    {
        readButton->setStyleSheet(activeStyle);


    }

    if (!reading) {
        readingButton->setEnabled(true);
        readingButton->setStyleSheet(defaultStyle);
    }
    else
    {
        readingButton->setStyleSheet(activeStyle);
    }

    if (!wantRead) {
        wantButton->setEnabled(true);
        wantButton->setStyleSheet(defaultStyle);
    }
    else
    {
        wantButton->setStyleSheet(activeStyle);
    }

    QFont font("Aptos Narrow");
    font.setStyleHint(QFont::Monospace);

    ui.displayL->setFont(font);
    ui.over4->setFont(font);

    //CSS END

    mainLayout->addWidget(imageLabel);

    textLayout->addLayout(buttonLayout);
    mainLayout->addLayout(textLayout);

    itemWidget->setLayout(mainLayout);



    QListWidgetItem* item = new QListWidgetItem();

    qDebug() << "Attempting to add >> ";
    item->setSizeHint(QSize(800, 180));
    ui.listWidget->addItem(item);
    ui.listWidget->setItemWidget(item, itemWidget);


}





void QTBOOKMETER::on_searchButton_clicked()
{
    QString searchQuery = ui.searchEdit->text();
    ui.listWidget->clear();
    resultCount = 0;
    
    
    API_Request(searchQuery);
    qDebug() << "API Request DONE";

    
}