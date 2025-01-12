#include "LoginDialog.h"


void LoginDialog::onLoginClicked()
{

    QSqlDatabase db = QSqlDatabase::database();

    bool loginComplete = false;

    if (!db.open()) {
        qDebug() << "Error: Could not connect to database." << db.lastError().text();
        return;
    }

    qDebug() << "Database connected successfully.";
    qDebug() << "Full database path:" << QFileInfo(db.databaseName()).absoluteFilePath();
    qDebug() << "Database file exists:" << QFile::exists(db.databaseName());
    qDebug() << "Tables:" << db.tables();

    QString username = usernameEdit->text();
    QString password = passwordEdit->text();

    db.transaction(); // Start transaction

    qDebug() << "TABLES:" << db.tables();

    QSqlQuery query(db); // Explicitly create query with database connection
    query.prepare("SELECT UserId FROM Users WHERE Username = ? AND Password = ?");
    query.addBindValue(username);
    query.addBindValue(password);

    if (query.exec()) {
        db.commit();
        if (query.next()) {
            loginComplete = true;
        }
        else {
            qDebug() << "Invalid username or password.";
           
            //QMessageBox::critical(nullptr, "Login Error!", "Invalid username or password.");
        }
    }
    else {
        db.rollback();
        qDebug() << "Query execution error:" << query.lastError().text();

    }





if (loginComplete) {
    accept();  
}
else {
   
    QMessageBox::warning(this, "Login Failed", "Invalid username or password.");
}


}

