#pragma once
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <qmessagebox.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <qfile.h>
#include <qfileinfo.h>
#include <qmessagebox.h>

class LoginDialog : public QDialog {
    Q_OBJECT

public:
    explicit LoginDialog(QWidget* parent = nullptr) : QDialog(parent) {
        setupLoginLayout();

        
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("C:\\Users\\xanda\\sql\\book_tracker.db");

        int nWidth = 500;
        int nHeight = 400;
        if (parent != NULL)
            setGeometry(parent->x() + parent->width() / 2 - nWidth / 2,
                parent->y() + parent->height() / 2 - nHeight / 2,
                nWidth, nHeight);
        else
            resize(nWidth, nHeight);

        setWindowTitle("Login");
        setWindowIcon(QIcon("C:\\Users\\xanda\\source\\repos\\QTBOOKMETER\\images\\app_icon.png"));
    }

    QString getUsername() const { return usernameEdit->text(); }
    QString getPassword() const { return passwordEdit->text(); }

private:
    void replaceLayout(QLayout* newLayout) {
        if (QLayout* currentLayout = layout()) {
            // Recursively delete all widgets and sub-layouts
            while (QLayoutItem* item = currentLayout->takeAt(0)) {
                if (QWidget* widget = item->widget()) {
                    widget->hide();
                    widget->deleteLater();
                }
                else if (QLayout* childLayout = item->layout()) {
                    // Recursively clear child layouts
                    QLayoutItem* childItem;
                    while ((childItem = childLayout->takeAt(0)) != nullptr) {
                        if (QWidget* childWidget = childItem->widget()) {
                            childWidget->hide();
                            childWidget->deleteLater();
                        }
                        delete childItem;
                    }
                }
                delete item;
            }
            delete currentLayout;
        }
        setLayout(newLayout);
        update();
    }

    void setupLoginLayout() {
        QVBoxLayout* mainLayout = new QVBoxLayout;

        QLabel* usernameLabel = new QLabel("Username:");
        QLabel* passwordLabel = new QLabel("Password:");

        usernameEdit = new QLineEdit();
        passwordEdit = new QLineEdit();
        passwordEdit->setEchoMode(QLineEdit::Password);

        QPushButton* loginButton = new QPushButton("Login");
        QPushButton* signUpButton = new QPushButton("Sign Up");

        connect(loginButton, &QPushButton::clicked, this, &LoginDialog::onLoginClicked);
        connect(signUpButton, &QPushButton::clicked, this, &LoginDialog::onSignUpClicked);


        //CSS AND STYLING

        usernameEdit->setStyleSheet("background-color: #1D1A32;padding: 5px 10px; border-radius: 15px; color: white;");
        usernameLabel->setStyleSheet("color: white;");
        usernameLabel->setFixedHeight(50);
        usernameEdit->setFixedHeight(60);


        passwordEdit->setStyleSheet("background-color: #1D1A32;padding: 5px 10px; border-radius: 15px; color: white;");
        passwordLabel->setStyleSheet("color: white;");
        passwordLabel->setFixedHeight(50);
        passwordEdit->setFixedHeight(60);


        //CSS END


        QVBoxLayout* usernameLayout = new QVBoxLayout;
        usernameLayout->addWidget(usernameLabel);
        usernameLayout->addWidget(usernameEdit);

        usernameLayout->setSpacing(0);
        usernameLayout->setContentsMargins(0, 0, 0, 0);




        QVBoxLayout* passwordLayout = new QVBoxLayout;
        passwordLayout->addWidget(passwordLabel);
        passwordLayout->addWidget(passwordEdit);

        passwordLayout->setSpacing(0);
        passwordLayout->setContentsMargins(0, 0, 0, 0);


        QHBoxLayout* buttonLayout = new QHBoxLayout;
        buttonLayout->addWidget(loginButton);
        buttonLayout->addWidget(signUpButton);


        mainLayout->addLayout(usernameLayout);
        mainLayout->addLayout(passwordLayout);
        mainLayout->addLayout(buttonLayout);


       

        replaceLayout(mainLayout);
    }

    void handleSignUp() {
        QVBoxLayout* signUpLayout = new QVBoxLayout;

        QLabel* newUsernameLabel = new QLabel("Username:");
        QLineEdit* newUsernameEdit = new QLineEdit();
        QLabel* newPasswordLabel = new QLabel("Password:");
        QLineEdit* newPasswordEdit = new QLineEdit();
        newPasswordEdit->setEchoMode(QLineEdit::Password);

        QPushButton* createAccountButton = new QPushButton("Create Account");
        QPushButton* backButton = new QPushButton("Back");

        //CSS

        newUsernameEdit->setStyleSheet("background-color: #1D1A32;padding: 5px 10px; border-radius: 15px; color: white;");
        newUsernameLabel->setStyleSheet("color: white;");
        newUsernameLabel->setFixedHeight(50);
        newUsernameEdit->setFixedHeight(60);


        newPasswordEdit->setStyleSheet("background-color: #1D1A32;padding: 5px 10px; border-radius: 15px; color: white;");
        newPasswordLabel->setStyleSheet("color: white;");
        newPasswordLabel->setFixedHeight(50);
        newPasswordEdit->setFixedHeight(60);

        //CSS END

        QSqlDatabase db = QSqlDatabase::database();

        connect(createAccountButton, &QPushButton::clicked, this, [=]() {
            QString username = newUsernameEdit->text();
            QString password = newPasswordEdit->text();

            QSqlQuery query(db);
            query.prepare("INSERT INTO Users (Username, Password) VALUES (:username, :password)");
            query.bindValue(":username", username);
            query.bindValue(":password", password);

            if (query.exec()) {
                QMessageBox::information(this, "Success", "New user created successfully. You can now login!");
                setupLoginLayout();
            }
            else {
                QMessageBox::warning(this, "Error", "Failed to create user: " + query.lastError().text());
            }
            });

        connect(backButton, &QPushButton::clicked, this, &LoginDialog::setupLoginLayout);

        QVBoxLayout* usernameLayout = new QVBoxLayout;
        usernameLayout->addWidget(newUsernameLabel);
        usernameLayout->addWidget(newUsernameEdit);

        usernameLayout->setSpacing(0);
        usernameLayout->setContentsMargins(0, 0, 0, 0);

        QVBoxLayout* passwordLayout = new QVBoxLayout;
        passwordLayout->addWidget(newPasswordLabel);
        passwordLayout->addWidget(newPasswordEdit);

        passwordLayout->setSpacing(0);
        passwordLayout->setContentsMargins(0, 0, 0, 0);

        QHBoxLayout* buttonLayout = new QHBoxLayout;
        buttonLayout->addWidget(createAccountButton);
        buttonLayout->addWidget(backButton);


        
        signUpLayout->addLayout(usernameLayout);
        signUpLayout->addLayout(passwordLayout);
        signUpLayout->addLayout(buttonLayout);

        replaceLayout(signUpLayout);
    }

private slots:
    void onLoginClicked();
    void onSignUpClicked() { handleSignUp(); }

private:
    QLineEdit* usernameEdit;
    QLineEdit* passwordEdit;
};