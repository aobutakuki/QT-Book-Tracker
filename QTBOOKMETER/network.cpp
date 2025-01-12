#include "network.h"



//API REQUEST
void QTBOOKMETER::API_Request(QString searchQuery) {

	QNetworkAccessManager* manager = new QNetworkAccessManager(this);
	connect(manager, &QNetworkAccessManager::finished,
		this, &QTBOOKMETER::replyFinished);

	qDebug() << "Attempting Query with :: " << searchQuery;
	QString maxResults = "&maxResults=40";
	QUrl url("https://www.googleapis.com/books/v1/volumes?q=" + searchQuery + maxResults);
	manager->get(QNetworkRequest(url));

	

}

void QTBOOKMETER::getUserId(int &currentUserId) {
   // QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //db.setDatabaseName("C:\\Users\\xanda\\sql\\book_tracker.db");

    QSqlDatabase db = QSqlDatabase::database();



    if (!db.open()) {
        qDebug() << "Error: Could not connect to database." << db.lastError().text();
        return;
    }

    qDebug() << "Database connected successfully.";
    qDebug() << "Full database path:" << QFileInfo(db.databaseName()).absoluteFilePath();
    qDebug() << "Database file exists:" << QFile::exists(db.databaseName());
    qDebug() << "Tables:" << db.tables();

    QString username = "username";
    QString password = "password1";

    db.transaction(); // Start transaction

    qDebug() << "TABLES:" << db.tables();

    QSqlQuery query(db); // Explicitly create query with database connection
    query.prepare("SELECT UserId FROM Users WHERE Username = ? AND Password = ?");
    query.addBindValue(username);
    query.addBindValue(password);

    if (query.exec()) {
        db.commit();
        if (query.next()) {
            int userID = query.value(0).toInt();
            qDebug() << "User logged in with ID:" << userID;
            currentUserId = userID;
        }
        else {
            qDebug() << "Invalid username or password.";
        }
    }
    else {
        db.rollback();
        qDebug() << "Query execution error:" << query.lastError().text();
    }
}


void QTBOOKMETER::replyFinished(QNetworkReply* reply) {

	qDebug() << "Processing Reply...";
	QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
	QJsonObject obj = doc.object();

	QJsonArray items = obj["items"].toArray();

	for (const QJsonValue& value : items) {

		qDebug() << "Loop starting...";
		resultCount++;

        QJsonObject bookObject = value.toObject();
        QString API_BookId = bookObject["id"].toString();

		QJsonObject book = value.toObject()["volumeInfo"].toObject();
		QString title = book["title"].toString();
		QString author = book.contains("authors") ? book["authors"].toArray().first().toString() : "Unknown";;
		int pageCount = book.contains("pageCount") ? book["pageCount"].toInt() : 0;;
		QString coverUrl = book["imageLinks"].toObject()["thumbnail"].toString();
       

		qDebug() << "START Add to list (" << title << "," << author << "," << pageCount << "," << coverUrl;
		addBookToList(title, author, pageCount, coverUrl,currentUserId,API_BookId);
	}




}

void QTBOOKMETER::checkDatabase(int userId, QString API_BookId, bool& read, bool& reading, bool& wantRead) 
{
    QSqlDatabase db = QSqlDatabase::database();

    QSqlQuery query(db);
    query.prepare("SELECT Status FROM UserBooks WHERE UserId = :userId AND GoogleBooksId = :googleBooksId");
    query.bindValue(":userId", userId);
    query.bindValue(":googleBooksId", API_BookId);

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return;
    }

    if (query.next()) {
        QString status = query.value(0).toString();
        qDebug() << "Status found:" << status;


        if (status == "Read") {
            qDebug() << "Status is Read.";
            read = true;
        }
        else if (status == "Reading") {
            qDebug() << "Status is Reading.";
            reading = true;
        }
        else if (status == "Want to Read") {
            qDebug() << "Status is Want to Read.";
            wantRead = true;
        }
        else {
            qDebug() << "Unknown status.";
        }
    }
    else {
        qDebug() << "No match found for UserId:" << userId << "and GoogleBooksId:" << API_BookId;
    }


}
