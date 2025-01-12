/********************************************************************************
** Form generated from reading UI file 'QTBOOKMETER.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTBOOKMETER_H
#define UI_QTBOOKMETER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QTBOOKMETERClass
{
public:
    QWidget *centralWidget;
    QListWidget *listWidget;
    QLineEdit *searchEdit;
    QPushButton *searchButton;
    QLabel *displayL;
    QLabel *over4;
    QPushButton *profileButton;
    QPushButton *iconLabel;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QTBOOKMETERClass)
    {
        if (QTBOOKMETERClass->objectName().isEmpty())
            QTBOOKMETERClass->setObjectName("QTBOOKMETERClass");
        QTBOOKMETERClass->resize(1250, 879);
        QTBOOKMETERClass->setStyleSheet(QString::fromUtf8("QMainWindow {background-color: #131121}\n"
"QLabel {color: white}"));
        centralWidget = new QWidget(QTBOOKMETERClass);
        centralWidget->setObjectName("centralWidget");
        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(40, 150, 1041, 681));
        listWidget->viewport()->setProperty("cursor", QVariant(QCursor(Qt::CursorShape::ArrowCursor)));
        listWidget->setAutoFillBackground(false);
        listWidget->setStyleSheet(QString::fromUtf8("QListWidget { background-color: #1D1A32; border-radius: 25px;}"));
        listWidget->setSpacing(10);
        listWidget->setViewMode(QListView::ViewMode::ListMode);
        listWidget->setModelColumn(0);
        searchEdit = new QLineEdit(centralWidget);
        searchEdit->setObjectName("searchEdit");
        searchEdit->setGeometry(QRect(220, 40, 631, 31));
        searchEdit->setStyleSheet(QString::fromUtf8("QLineEdit {    background-color: #1D1A32;\n"
"    color: white;\n"
"    border-radius: 9px;\n"
"    padding: 5px; \n"
"}"));
        searchButton = new QPushButton(centralWidget);
        searchButton->setObjectName("searchButton");
        searchButton->setGeometry(QRect(870, 40, 41, 31));
        searchButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #1D1A32;\n"
"    color: white;\n"
"    border-radius: 9px;\n"
"    padding: 5px; \n"
"}"));
        displayL = new QLabel(centralWidget);
        displayL->setObjectName("displayL");
        displayL->setGeometry(QRect(460, 90, 181, 31));
        over4 = new QLabel(centralWidget);
        over4->setObjectName("over4");
        over4->setGeometry(QRect(250, 120, 621, 20));
        profileButton = new QPushButton(centralWidget);
        profileButton->setObjectName("profileButton");
        profileButton->setGeometry(QRect(50, 10, 100, 100));
        profileButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #1D1A32;\n"
"    color: white;\n"
"    border-radius: 50px;  /* Half of the width/height */\n"
"    height: 100px;         /* Set fixed height */\n"
"    width: 100px;          /* Set fixed width */\n"
"    border: 4px solid white;\n"
"}"));
        iconLabel = new QPushButton(centralWidget);
        iconLabel->setObjectName("iconLabel");
        iconLabel->setGeometry(QRect(980, 10, 91, 81));
        iconLabel->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #1D1A32;\n"
"    color: white;\n"
"    border-radius: 9px;\n"
"    padding: 5px; \n"
"}"));
        QTBOOKMETERClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(QTBOOKMETERClass);
        mainToolBar->setObjectName("mainToolBar");
        QTBOOKMETERClass->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QTBOOKMETERClass);
        statusBar->setObjectName("statusBar");
        QTBOOKMETERClass->setStatusBar(statusBar);

        retranslateUi(QTBOOKMETERClass);

        listWidget->setCurrentRow(-1);


        QMetaObject::connectSlotsByName(QTBOOKMETERClass);
    } // setupUi

    void retranslateUi(QMainWindow *QTBOOKMETERClass)
    {
        QTBOOKMETERClass->setWindowTitle(QCoreApplication::translate("QTBOOKMETERClass", "QTBOOKMETER", nullptr));
#if QT_CONFIG(whatsthis)
        searchButton->setWhatsThis(QCoreApplication::translate("QTBOOKMETERClass", "<html><head/><body><p><span style=\" text-decoration: underline;\">Important note:</span></p><p><br/></p><p>Make sure to always input the <span style=\" font-weight:700;\">full title</span> on the search bar.</p><p>If you are looking for a series or multiple volumes specify either <span style=\" font-weight:700;\">volume number</span> or <span style=\" font-weight:700;\">volume full title<br/><br/></span><span style=\" text-decoration: underline;\">Example queue:</span><br/>&quot;harry potter <span style=\" font-style:italic;\">prisoner of azkaban</span>&quot;</p><p>&quot;spyx family <span style=\" font-style:italic;\">1</span>&quot;</p><p><br/></p><p>If even then you can't find what you are looking for, try being more specific</p><p>You can also try the <span style=\" font-weight:700;\">ISBN, author name, &quot;vol&quot;, </span>etc<br/><br/><span style=\" text-decoration: underline;\">Specific e</span><span style=\" text-decoration: underline;\">xample queue:</span><span style=\" text-decoration: underline;\""
                        "><br/></span>&quot;Harry Potter <span style=\" font-style:italic;\">and the</span> Prisioner of Azkaban <span style=\" font-style:italic;\">J.K Rowling</span>&quot;<br/>&quot;Spy <span style=\" font-style:italic;\">x</span> Family<span style=\" font-style:italic;\"> vol. </span>1 <span style=\" font-style:italic;\">Tatsuya Endo</span>&quot;</p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        searchButton->setText(QString());
        displayL->setText(QString());
        over4->setText(QString());
        profileButton->setText(QString());
        iconLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class QTBOOKMETERClass: public Ui_QTBOOKMETERClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTBOOKMETER_H
